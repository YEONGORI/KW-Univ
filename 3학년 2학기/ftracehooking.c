#include "ftracehooking.h"

int read_byte = 0, write_byte = 0;

int open_count = 0; // 시스템 콜의 호출 횟수를 담은 변수들
int close_count = 0;
int read_count = 0;
int write_count = 0;
int lseek_count = 0;

pid_t cur_pid = 0;

char kernel_buffer[BUFF_SIZE] = {
	0,
}; // 커널 버퍼 변수
char *cur_process;

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *); //
static sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_ftrace;

static asmlinkage int ftrace(const struct pt_regs *regs);

EXPORT_SYMBOL(read_byte); // EXPORT를 사용해 변수들을 심볼릭 테이블에 연결
EXPORT_SYMBOL(write_byte);

EXPORT_SYMBOL(open_count);
EXPORT_SYMBOL(close_count);
EXPORT_SYMBOL(read_count);
EXPORT_SYMBOL(write_count);
EXPORT_SYMBOL(lseek_count);

EXPORT_SYMBOL(kernel_buffer);
EXPORT_SYMBOL(cur_pid);

void make_rw(void *addr)
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level);

	if (pte->pte & ~_PAGE_RW)
		pte->pte |= _PAGE_RW;
}

void make_ro(void *addr)
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level);

	pte->pte = pte->pte & ~_PAGE_RW;
}

static int __init hooking_init(void)
{
	syscall_table = (sys_call_ptr_t *)kallsyms_lookup_name("sys_call_table");

	make_rw(syscall_table);
	real_ftrace = syscall_table[__NR_ftrace];
	syscall_table[__NR_ftrace] = (sys_call_ptr_t)ftrace;
	return 0;
}

static void __exit hooking_exit(void)
{
	syscall_table[__NR_ftrace] = real_ftrace;
	make_ro(syscall_table);
}

static asmlinkage int ftrace(const struct pt_regs *regs)
{
	if (regs->di == 0)
	{ // change process name
		printk(KERN_INFO "[2018202076] %s file[%s] start [x] read - %d / written - %d\n", cur_process, kernel_buffer, read_byte, write_byte);
		printk(KERN_INFO "open[%d] close[%d] read[%d] write[%d] lseek[%d]\n", open_count, close_count, read_count, write_count, lseek_count);
		printk(KERN_INFO "OS Assignment 2 ftrace [%d] End\n", cur_pid);
		return 0;
	}
	else
	{
		struct task_struct *task = current;
		cur_process = task->comm;
		cur_pid = regs->di;
		printk(KERN_INFO "OS Assignment 2 ftrace [%d] Start\n", cur_pid);
		return 0;
	}
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
