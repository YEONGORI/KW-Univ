#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define ADDRESS_LED 0x14805000

int main(void)
{
	unsigned char *addr_led;
	int fd;

	if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
	{
		perror("mem open fail\n");
		exit(1);
	}
	addr_led = (unsigned char *)mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, fd, ADDRESS_LED);

	if (addr_led < 0)
	{
		close(fd);
		printf("mmap error\n");
		exit(1);
	}

	for (int i = 0; i < 256; i++)
	{
		*addr_led = i;
		usleep(100000);
	}

	munmap(addr_led, 4096);
	close(fd);
	return 0;
}