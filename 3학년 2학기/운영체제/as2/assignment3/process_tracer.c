// every code including wrapping
#include "sched.h"

int fork_count = 0;
pid_t cur_pid = 0;

char *cur_process;

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *); //
static sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_process_tracer;

static asmlinkage int process_tracer(const struct pt_regs *regs);

EXPORT_SYMBOL(fork_count);
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
	real_process_tracer = syscall_table[__NR_process_tracer];
	syscall_table[__NR_process_tracer] = (sys_call_ptr_t)process_tracer;
	return 0;
}

static void __exit hooking_exit(void)
{
	syscall_table[__NR_process_tracer] = real_process_tracer;
	make_ro(syscall_table);
}

static asmlinkage pid_t process_tracer(const struct pt_regs *regs)
{
    struct task_struct *task = current;
    cur_process = task->comm;
    cur_pid = regs->di;
    printk(KERN_INFO "##### TASK INFORMATION OF ''[%d] %s'' #####", cur_pid, cur_process);
    printk(KERN_INFO "- task state : ", );


	if (regs->di == 0)
	{ // change process name
		printk(KERN_INFO "[2018202076] %s file[%s] start [x] read - %d / written - %d\n", cur_process, kernel_buffer, read_byte, write_byte);
		printk(KERN_INFO "open[%d] close[%d] read[%d] write[%d] lseek[%d]\n", open_count, close_count, read_count, write_count, lseek_count);
		printk(KERN_INFO "OS Assignment 2 process_tracer [%d] End\n", cur_pid);
		return 0;
	}
	else
	{
		struct task_struct *task = current;
		cur_process = task->comm;
		cur_pid = regs->di;
		printk(KERN_INFO "OS Assignment 2 process_tracer [%d] Start\n", cur_pid);
		return 0;
	}
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
