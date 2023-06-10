#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdint.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <sys/types.h>

int	segment_id, page_size;

uint8_t* Operation;
uint8_t* compiled_code;

void sharedmem_init();
void sharedmem_exit();
void drecompile_init();
void drecompile_exit();
void* drecompile(uint8_t *func);

int main(void)
{
	int (*func)(int a);
	clock_t start, end;

	start = clock();

	sharedmem_init();
	drecompile_init();

	func = (int (*)(int a))drecompile(Operation);

	for (int i = 0; i < 100000; i++)
		func(1);

	drecompile_exit();
	sharedmem_exit();

	end = clock();
	printf("Total execution time %lf sec\n", (double)(end-start)/CLOCKS_PER_SEC);

	return 0;
}

void sharedmem_init()
{
	page_size = getpagesize();
	segment_id = shmget(1234, page_size, IPC_CREAT | S_IRUSR | S_IWUSR);
	Operation = (uint8_t*)shmat(segment_id, NULL, 0);
}

void sharedmem_exit()
{
	shmdt(Operation);
	shmctl(segment_id, IPC_RMID, NULL);
}

void drecompile_init()
{
	int fd = open("text", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
	compiled_code = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	compiled_code = Operation;
}

void drecompile_exit()
{
	munmap(compiled_code, page_size);
}

void* drecompile(uint8_t* func)
{
	// compiled_code = func;
	int i = 0, j = 0, dl_reg = 0;
	uint8_t dl_val = 0;
#ifdef dynamic
	while (func[i] != 0xc3 && func[i] != 0xC3) {
		uint8_t tmp = 0;
		if (func[i] == 0xb2) // get dl
		{
			dl_val = func[i + 1];
			dl_reg = i;
		}
		if (func[i] == 0x83) // add || sub
		{
			for (; func[i] == 0x83; i += 3)
				tmp += func[i + 2];
			compiled_code[j++] = func[i - 3];
			compiled_code[j++] = func[i - 2];
			compiled_code[j++] = tmp;
		}
		else if (func[i] == 0x6b) // imul
		{
			tmp = 1;
			for (; func[i] == 0x6b; i += 3)
				tmp *= func[i + 2];
			compiled_code[j++] = func[i - 3];
			compiled_code[j++] = func[i - 2];
			compiled_code[j++] = tmp;
		}
		else if (func[i] == 0xf6) // div
		{
			tmp = 1;
			for (; func[i] == 0xf6; i += 2)
				tmp *= dl_val;
			compiled_code[j++] = func[i - 2];
			compiled_code[j++] = func[i - 1];
			compiled_code[dl_reg + 1] = tmp;
		}
		else // nothing
			compiled_code[j++] = func[i++];
	}
	compiled_code[j] = 0xc3;
#endif
	mprotect(compiled_code, page_size, PROT_READ | PROT_EXEC);
	return compiled_code;
}
