#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/ioport.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/ioctl.h>
#include <asm/hardware.h>
#include <asm/uaccess.h>
#include <asm/fcntl.h>

#define DRIVER_AUTHOR "Hanback Electronics"
#define DRIVER_DESC "7 Segment test"
#define SEGMENT_MODULE_VERSION "7 Segment PORT V0.1"
#define SEGMENT_NAME "7 Segment"
#define SEGMENT_MAJOR_NUMBER 0
#define SEGMENT_ADDRESS 0x14800000
#define SEGMENT_ADDRESS_RANGE 0x2000

static unsigned int segment_usage = 0;
static unsigned int segment_major = 0;
static unsigned int segment_ioremap;
static unsigned char *segment_data;
static unsigned char *segment_grid;

int segment_open(struct inode *inode, struct file *filp)
{
	if (segment_usage != 0)
		return -EBUSY;
	segment_ioremap = (unsigned int)ioremap(SEGMENT_ADDRESS, SEGMENT_ADDRESS_RANGE);
	if (!check_mem_region(segment_ioremap, SEGMENT_ADDRESS_RANGE))
		request_region(segment_ioremap, SEGMENT_ADDRESS_RANGE, SEGMENT_NAME);
	else
		printk(KERN_WARNING "Can't get IO Region 0x%x\n", segment_ioremap);
	segment_grid = (unsigned char *)(segment_ioremap);
	segment_data = (unsigned char *)(segment_ioremap + 0x1000);
	segment_usage = 1;
	return 0;
}

int segment_release(struct inode *inode, struct file *filp)
{
	release_region(segment_ioremap, SEGMENT_ADDRESS_RANGE);
	iounmap((unsigned char *)segment_ioremap);
	segment_usage = 0;
	return 0;
}

unsigned char Getsegmentcode(char x)
{
	unsigned char code;
	switch (x)
	{
	case 0x0:
		code = 0x3f;
		break;
	case 0x1:
		code = 0x06;
		break;
	case 0x2:
		code = 0x5b;
		break;
	case 0x3:
		code = 0x4f;
		break;
	case 0x4:
		code = 0x66;
		break;
	case 0x5:
		code = 0x6d;
		break;
	case 0x6:
		code = 0x7d;
		break;
	case 0x7:
		code = 0x07;
		break;
	case 0x8:
		code = 0x7f;
		break;
	case 0x9:
		code = 0x6f;
		break;
	case 0xA:
		code = 0x77;
		break;
	case 0xB:
		code = 0x7c;
		break;
	case 0xC:
		code = 0x39;
		break;
	case 0xD:
		code = 0x5e;
		break;
	case 0xE:
		code = 0x79;
		break;
	case 0xF:
		code = 0x71;
		break;
	default:
		code = 0;
		break;
	}
	return code;
}

ssize_t segment_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what)
{
	unsigned char data[6];
	unsigned char digit[6] = {0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	unsigned int i, j, num, ret;
	unsigned int count = 0, temp1, temp2;
	ret = copy_from_user(&num, gdata, 4);
	if (ret < 0)
		return -1;
	while (count < num + 1)
	{
		data[5] = Getsegmentcode(count / 100000);
		temp1 = count % 100000;
		data[4] = Getsegmentcode(temp1 / 10000);
		temp2 = temp1 % 10000;
		data[3] = Getsegmentcode(temp2 / 1000);
		temp1 = temp2 % 1000;
		data[2] = Getsegmentcode(temp1 / 100);
		temp2 = temp1 % 100;
		data[1] = Getsegmentcode(temp2 / 10);
		data[0] = Getsegmentcode(temp2 % 10);
		for (j = 0; j < 100; j++)
		{
			for (i = 0; i < 6; i++)
			{
				*segment_grid = ~digit[i];
				*segment_data = data[i];
				mdelay(1);
			}
		}
		count++;
	}
	return length;
}

struct file_operations segment_fops
{
	.owner = THIS_MODULE,
	.open = segment_open,
	.write = segment_write,
	.release = segment_release,
};

int segment_init(void)
{
	int result;

	result = register_chrdev(SEGMENT_MAJOR_NUMBER, SEGMENT_NAME, &segment_fops);
	if (result < 0)
	{
		printk(KERN_WARNING "Can't get any major\n");
		return result;
	}
	segment_major = result;
	printk("init module, 7segment major number : %d\n", result);
	return 0;
}

void segment_exit(void)
{
	unregister_chrdev(segment_major, SEGMENT_NAME);
}

module_init(segment_init);
module_exit(segment_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	int value;

	if ((fd = open("/dev/7segment", O_RDWR | O_SYNC)) < 0)
	{
		printf("FND open fail\n");
		exit(1);
	}

	while (value != 0)
	{
		printf("input counter value : (0 : exit program) \n");
		scanf("%d", &value);
		write(fd, &value, 4);
	}
	close(fd);
	return 0;
}