#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <asm/fcntl.h>

unsigned char Getsegcode(unsigned char x);

#define SEGMENT1 0x14800000 // digit register
#define SEGMENT2 0x14801000 // data register

unsigned char Getsegcode(unsigned char x)
{
	unsigned char code;

	switch (x)
	{
	case 0:
		code = 0x3f;
		break;
	case 1:
		code = 0x06;
		break;
	case 2:
		code = 0x5b;
		break;
	case 3:
		code = 0x4f;
		break;
	case 4:
		code = 0x66;
		break;
	case 5:
		code = 0x6d;
		break;
	case 6:
		code = 0x7d;
		break;
	case 7:
		code = 0x07;
		break;
	case 8:
		code = 0x7f;
		break;
	case 9:
		code = 0x6f;
		break;
	default:
		code = 0;
		break;
	}
	return code;
}

int main(char argc, char **argv)
{
	unsigned char *addr_seg1, *addr_seg2;
	char data[6];
	char digit[6] = {0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	int fd, i, j, k;
	int count = 0, temp1, temp2, value;

	if (argc == 1)
		value = 50;
	else if (argc == 2)
	{
		value = strtol(&argv[1][0], NULL, 10);
		if (value > 100)
			value = 100;
	}
	else
		printf("please input the parameter![1-100] ex) ./7segment 10\n");

	if ((fd = open("/dev/7segment", O_RDWR | O_SYNC)) < 0)
	{
		perror("device file open is failed\n");
		exit(1);
	}

	addr_seg1 = (unsigned char *)mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, fd, SEGMENT1);
	addr_seg2 = (unsigned char *)mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, fd, SEGMENT2);

	if (addr_seg1 < 0 || addr_seg2 < 0)
	{
		close(fd);
		perror("mmap error\n");
		exit(1);
	}

	while (count < value)
	{
		data[5] = Getsegcode(count / 100000);
		temp1 = count % 100000;
		data[4] = Getsegcode(temp1 / 10000);
		temp2 = temp1 % 10000;
		data[3] = Getsegcode(temp2 / 1000);
		temp1 = temp2 % 1000;
		data[2] = Getsegcode(temp1 / 100);
		temp2 = temp1 % 100;
		data[1] = Getsegcode(temp2 / 10);
		data[0] = Getsegcode(temp2 % 10);

		for (j = 0; j < 50; j++)
		{
			for (i = 0; i < 6; i++)
			{
				*addr_seg1 = -digit[i];
				*addr_seg2 = data[i];
				for (k = 0; k < 65536; k++)
					;
			}
		}
		count++;
	}

	usleep(1000);
	munmap(addr_seg1, 4096);
	munmap(addr_seg2, 4096);
	close(fd);
	return 0;
}