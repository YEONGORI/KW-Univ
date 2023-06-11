#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/kernel.h>
#include <linux/ioport.h>

#define LED_NAME LED
#define LED_ADDRESS 0x14805000
#define LED_ADDRESS_RANGE 0x1000

static int led_usage = 0;
static int led_major = 0;
static unsigned int led_ioremap;

int led_open(struct inode *inode, struct file *file) // 중요
{
	if (led_usage != 0)
		return -EBUSY;

	led_ioremap = (unsigned int)ioremap(LED_ADDRESS, LED_ADDRESS_RANGE);

	if (!check_mem_region(led_ioremap, LED_ADDRESS_RANGE))
		request_region(led_ioremap, LED_ADDRESS_RANGE, LED_NAME);
	else
		printk("Can't get IO Region 0x%x\n", led_ioremap);
	led_usage = 1;
	return 0;
}

int led_release(struct inode *inode, struct file *file)
{
	release_region(led_ioremap, LED_ADDRESS_RANGE);
	iounmap((unsigned char *)led_ioremap);
	led_usage = 0;
	return 0;
}

ssize_t led_write(struct file *inode, const char *buf, size_t count, loff_t *loff)
{
	unsigned char *addr;
	unsigned char c;
	get_user(c, buf);
	addr = (unsigned char *)(led_ioremap);
	*addr = c;
	return length;
}

static struct file_operations led_fops
{
	.owner = THIS_MODULE,
	.write = led_write,
	.open = led_open,
	.release = led_release,
};

int led_init(void) // 중요
{
	led_major = register_chrdev(0, LED_NAME, &led_fops); // 중요
	if (led_major < 0)
	{
		printk("Can't get any major\n");
		return led_major;
	}

	printk("init module, led major number: %d\n", led_major);
	return 0;
}

void led_exit(void)
{
	unregister_chrdev(led_major, LED_NAME); // 중요
	printk("driver: %s DRIVER EXIT\n", LED_NAME);
}

module_init(led_init);
module_exit(led_exit);

// $ insmod
// $ mknod /dev/led c 240 0
// $ ./led
