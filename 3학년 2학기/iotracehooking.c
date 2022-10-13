#include "ftracehooking.h"

extern int read_byte;
extern int write_byte;

extern int open_count;
extern int close_count;
extern int read_count;
extern int write_count;
extern int lseek_count;

extern char kernel_buffer[BUFF_SIZE];
extern pid_t cur_pid;

pid_t get_cur_pid(void) // 유저모드에서 get_cur_pid와 같은 역할을 함
{
	pid_t pid = 0;
	struct task_struct *task = current; //이 부분으로 인해 해당 프로세스에서의 pid 가져올 수 있음
	pid = task->pid;
	return pid;
}

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);
static sys_call_ptr_t *sys_call_table;

sys_call_ptr_t real_open;
sys_call_ptr_t real_close;
sys_call_ptr_t real_read;
sys_call_ptr_t real_write;
sys_call_ptr_t real_lseek;

static asmlinkage long ftrace_open(const struct pt_regs *regs)
{

	if (cur_pid == get_cur_pid()) // kernel has many process
	{	
		//유저 공간에 위치한 문자열 메모리 공간을 커널에서 이용하기 위하여
		//커널 공간에 버퍼를 잡고 문자열을 복사하는 과정.
		open_count++;
		strncpy_from_user(kernel_buffer, (const char __user *)regs->di, BUFF_SIZE);
	}
	return real_open(regs);
}

static asmlinkage long ftrace_close(const struct pt_regs *regs)
{
	// printk(KERN_INFO "OS Assignment2 ftrace_close Start\n");
	if (cur_pid == get_cur_pid())
	{
		close_count++;
	}
	return real_close(regs);
}

static asmlinkage long ftrace_read(const struct pt_regs *regs)
{
	// printk(KERN_INFO "OS Assignment2 ftrace_read Start\n");
	if (cur_pid == get_cur_pid())
	{
		read_byte = read_byte + ((int)regs->dx); // read 바이트를 카운트 하는 과정
		read_count++;
	}
	return real_read(regs);
}
static asmlinkage long ftrace_write(const struct pt_regs *regs)
{
	// printk(KERN_INFO "OS Assignment2 ftrace_write Start\n");
	if (cur_pid == get_cur_pid())
	{
		write_byte = write_byte + ((int)regs->dx); // write 바이트를 카운트 하는 과정
		write_count++;
	}
	return real_write(regs);
}
static asmlinkage long ftrace_lseek(const struct pt_regs *regs)
{
	// printk(KERN_INFO "OS Assignment2 ftrace_lseek Start\n");

	if (cur_pid == get_cur_pid())
	{
		lseek_count++;
	}
	return real_lseek(regs);
}

static int __init hooking_init(void)
{
	sys_call_table = (sys_call_ptr_t *)kallsyms_lookup_name("sys_call_table");
	// make_rw(sys_call_table);//이것은 ftracehooking.c에 이미 정의했기 때문에 또 하면 에러남
	real_open = sys_call_table[__NR_open];
	real_close = sys_call_table[__NR_close];
	real_read = sys_call_table[__NR_read];
	real_write = sys_call_table[__NR_write];
	real_lseek = sys_call_table[__NR_lseek];

	sys_call_table[__NR_open] = ftrace_open;
	sys_call_table[__NR_close] = ftrace_close;
	sys_call_table[__NR_read] = ftrace_read;
	sys_call_table[__NR_write] = ftrace_write;
	sys_call_table[__NR_lseek] = ftrace_lseek;
	return 0;
}

static void __exit hooking_exit(void)
{
	sys_call_table[__NR_open] = real_open;
	sys_call_table[__NR_close] = real_close;
	sys_call_table[__NR_read] = real_read;
	sys_call_table[__NR_write] = real_write;
	sys_call_table[__NR_lseek] = real_lseek;
	// make_ro(sys_call_table);//이것은 ftracehooking.c에 이미 정의했기 때문에 또 하면 에러남
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
