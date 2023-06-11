#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
	printk("Hello, world\n");
	return 0;
}

static int hello_exit(void)
{
	printk("Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");

/* CMD */
// $ insmod hello.ko
// $ lsmod
// dmesg | tail -n 5