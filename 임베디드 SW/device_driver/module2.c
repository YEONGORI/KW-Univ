#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>

#define CHR_DEV_NAME "test_dev"
#define CHR_DEV_MAJOR 240

int chr_open(struct inode *inode, struct file *filp)
{
	int number = MINOR(inode->i_rdev);
	printk("Virtual Character Device Open: Minor Number is %d\n", number);
	return 0;
}

ssize_t chr_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	printk("write data: %s\n", buf);
	return count;
}

ssize_t chr_read(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	printk("read data: %s\n", buf);
	return count;
}

int chr_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch (cmd)
	{
	case 0:
		printk("cmd value is %d\n", cmd) break;
	case 1:
		printk("cmd value is %d\n", cmd);
		break;
	}
	return 0;
}

int chr_release(struc inode *inode, struct file *filp)
{
	printk("Virtual Character Device Release\n");
	return 0;
}

struct file_operations chr_fops
{
	.owner = THIS_MODULE,
	.ioctl = chr_ioctl,
	.write = chr_write,
	.read = chr_read,
	.open = chr_open,
	.release = chr_release,
};

int sample_init(void)
{
	int registration;

	printk("Registration Character Device to Kernel\n");
	registration = register_chrdev(CHR_DEV_MAJOR, CHR_DEV_NAME, &chr_fops);
	if (registration < 0)
		return registration;
	printk("Major Number: %d\n", registration);
	return 0;
}

void sample_cleanup(void)
{
	printk("Unregistration Character Device to Kernel\n");
	unregister_chrdev(CHR_DEV_MAJOR, CHR_DEV_NAME);
}

MODULE_LICENSE("GPL");
module_init(sample_init);
module_init(sample_cleanup);

/* APPLICATION */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DEVICE_FILE_NAME "/dev/chr_dev"

int main(int argc, char **argv)
{
	int device;
	char wbuf[128] = "Write buffer data";
	char rbuf[128] = "Read buffer data";
	int n = atoi(argv[1]);

	device = open(DEVICE_FILE_NAME, O_RDWR | O_NDELAY);
	if (device >= 0)
	{
		printf("Device file Open\n");
		ioctl(device, n);
		write(device, wbuf, 10);
		printf("write value is %s\n", wbuf);
		read(device, rbuf, 10);
		printf("read value is %s\n", rbuf);
	}
	else
		perror("Device file open fail");
	return 0;
}

/* CMD */
// $ insmod chr_dev.o
// $ mknod /dev/chr_dev c240 0
// $ ./chr_app 1