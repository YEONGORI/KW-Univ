#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "textlcd.h"

int main(int argc, char **argv)
{
	int i, dev;
	char buf[13] = "Hanback.co.kr";
	char welcome[14] = "welcome to the";
	char welcome2[16] = "embedded world!!";
	struct strcommand_varible strcommand;

	strcommand.rows = 0;
	strcommand.nfonts = 0;
	strcommand.display_enable = 1;
	strcommand.cursor_enable = 0;
	strcommand.nblink = 0;
	strcommand.set_screen = 0;
	strcommand.set_rightshit = 1;
	strcommand.increase = 1;
	strcommand.nshift = 0;
	strcommand.pos = 0;
	strcommand.command = 1;
	strcommand.strlength = 16;

	dev = open("/dev/textlcd", O_WRONLY | O_NDELAY);

	if (dev != -1)
	{
		write(dev, buf, 13);
		sleep(2);
		ioctl(dev, TEXTLCD_CLEAR, &strcommand, 32);
		strcommand.pos = 0;
		ioctl(dev, TEXTLCD_DD_ADDRESS, &strcommand, 32);
		for (i = 0; i < 14; i++)
		{
			memcpy(&strcommand.buf[0], &wellcom[i], sizeof(wellcom));
			ioctl(dev, TEXTLCD_WRITE_BYTE, &strcommand, 32);
		}
		sleep(2);
		strcommand.pos = 40;
		ioctl(dev, TEXTLCD_DD_ADDRESS, &strcommand, 32);
		for (i = 0; i < 16; i++)
		{
			memcpy(&strcommand.buf[0], &wellcom2[i], sizeof(wellcom2));
			ioctl(dev, TEXTLCD_WRITE_BYTE, &strcommand, 32);
		}
		close(dev);
	}
	else
	{
		printf("application : Device Open ERROR!\n");
		exit(1);
	}
	return 0;
}