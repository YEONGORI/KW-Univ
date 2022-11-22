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

	printf("func: %d\n", func(1));

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
	compiled_code = mmap(NULL, page_size * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	compiled_code = Operation;
}

void drecompile_exit()
{
	munmap(compiled_code, page_size);
}
/*
void* drecompile(uint8_t* func)
{
	int i = 0, j = 0;
// #ifdef dynamic
	while (Operation[i] != 0xc3 && Operation[i] != 0xC3) {
		uint8_t tmp = 0;
		if (Operation[i] == 0x83) // add || sub
		{
			for (; Operation[i] == 0x83 && Operation[i + 1] == 0xc0; i += 3)
				tmp += Operation[i + 2];
			compiled_code[j++] = Operation[i - 3];
			compiled_code[j++] = Operation[i - 2];
			compiled_code[j++] = tmp;
		}
		else if (Operation[i] == 0x6b) // imul
		{
			tmp = 1;
			for (; Operation[i] == 0x6b; i += 3)
				tmp *= Operation[i + 2];
			compiled_code[j++] = Operation[i - 3];
			compiled_code[j++] = Operation[i - 2];
			compiled_code[j++] = tmp;
		}
		else if (Operation[i] == 0xf6) // div
		{
			j++;
			i++;
			// compiled_code[j] = 
			compiled_code[j++] = Operation[i++];
		}
		else // nothing
		{
			compiled_code[j++] = Operation[i++];
		}
	}
	compiled_code[j] = 0xC3;
// #endif
	mprotect(compiled_code, page_size, PROT_READ | PROT_EXEC);
	return compiled_code;
}
*/

void* drecompile(uint8_t* func)
{
#ifdef dynamic
	int i = 0, j = 0;
	uint8_t code[3];

	// for all function instruction
	while(func[i] != 0xc3) {
		// operation, source register
		code[0] = func[i];

		// op is not target of optimization
		if(code[0] != 0x83 && code[0] != 0x6b && code[0] != 0xf6) {
			compiled_code[j++] = func[i++];
		}
		else {
			// init value
			code[1] = func[i+1];
			code[2] = code[0] == 0x83 ? 0 : 1;

			if(code[0] == 0xf6) {	// div
				// same code[0-1]
				while(func[i] == code[0] && func[i+1] == code[1]) {
					code[2] *= func[i-1];

					// if repeated div, i=i+4
					// else,	    i=i+2
					i = func[i+4] == code[0] ? i+4 : i+2;
				}
				compiled_code[j-1] = code[2];
				compiled_code[j++] = code[0];
				compiled_code[j++] = code[1];
			}
			else {			// not div
				// same code[0-1]
				while(func[i] == code[0] && func[i+1] == code[1]) {
					if(code[0] == 0x83) // add suv
						code[2] += func[i+2];
					else		    // imul
						code[2] *= func[i+2];
					i += 3;
				}
				compiled_code[j++] = code[0];
				compiled_code[j++] = code[1];
				compiled_code[j++] = code[2];
			}
		}
	}
	// end of func
	compiled_code[j] = func[i];
#endif

	// chmod r-x
	mprotect(compiled_code, PAGE_SIZE, PROT_READ | PROT_EXEC);

	return compiled_code;
}