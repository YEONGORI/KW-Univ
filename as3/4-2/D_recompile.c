#include <stdio.h>
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

void sharedmem_init(); // ���� �޸𸮿� ����
void sharedmem_exit();
void drecompile_init(); // memory mapping ���� 
void drecompile_exit(); 
void* drecompile(uint8_t *func); //����ȭ�ϴ� �κ�

int main(void)
{
	int (*func)(int a);
	int i;

	sharedmem_init();
	drecompile_init();

	func = (int (*)(int a))drecompile(Operation);

	drecompile_exit();
	sharedmem_exit();
	return 0;
}

void sharedmem_init()
{
	segment_id = shmget(1234, PAGE_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);
	Operation = (uint8_t*)shmat(segment_id, NULL, 0);

}

void sharedmem_exit()
{
	shmdt(Operation);
	shmctl(segment_id, IPC_RMID, NULL);
}

void drecompile_init()
{
	page_size = getpagesize();

	compiled_code = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
	memcpy(compiled_code, Operation, page_size);
}

void drecompile_exit()
{
	munmap(compiled_code, page_size);
}

void* drecompile(uint8_t* func)
{
	int i = 0, j = 0;
	uint8_t tmp;

#ifdef DYNAMIC
	while (func[i] != 0xc3) {
		tmp = 0;
		if (func[i] == 0x83 && func[i + 1] == 0xc0) // add
		{
			for (; func[i] == 0x83 && func[i + 1] == 0xc0; i += 3)
				tmp += func[i + 2];
			compiled_code[j++] = func[i - 3];
			compiled_code[j++] = func[i - 2];
			compiled_code[j++] = tmp;
			// while (func[i] == 0x83 && func[i + 1] == 0xc0)
			// {
			// 	tmp += func[i + 2];
			// 	i += 3;
			// }

		}
		else if (func[i] == 0x83 && func[i + 1] == 0xe8) // sub
		{
			for (; func[i] == 0x83 && func[i + 1] == 0xc0; i += 3)
				tmp -= func[i + 2];
			compiled_code[j++] = func[i - 3];
			compiled_code[j++] = func[i - 2];
			compiled_code[j++] = tmp;
			// while (func[i] == 0x83 && func[i + 1] == 0xc0)
			// {
			// 	tmp -= func[i + 2];
			// 	i += 3;
			// }
		}
		else if (func[i] == 0x6b) // imul
		{
			tmp = 1;
			for (; func[i] == 0x83 && func[i + 1] == 0xc0; i += 3)
				tmp *= func[i + 2];
			compiled_code[j++] = func[i - 3];
			compiled_code[j++] = func[i - 2];
			compiled_code[j++] = tmp;
			// while (func[i] == 0x6b)
			// {
			// 	tmp
			// }
		}
		else if (func[i] == 0xf6) // div
		{
			i += 2;
			// while (func[i] == 0xf6)
			// {
			// 	tmp *= func[i + 2];
			// 	i += 3;
			// }
		}
		else
			compiled_code[j++] = func[i++];
	}
	compiled_code[j] = func[i];
#endif
	mprotect(compiled_code, page_size, PROT_READ | PROT_EXEC);
	return compiled_code;
}

