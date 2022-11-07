// every code including wrapping
#include "sched.h"

int fork_count = 0;
pid_t cur_pid = 0;

char *cur_process;

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);
static sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_process_tracer;

static asmlinkage pid_t process_tracer(pid_t trace_task);

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

static asmlinkage pid_t process_tracer(pid_t trace_task)
{
    struct task_struct *task = current;
    cur_pid = trace_task;

	for_each_process(task) {
		if (cur_pid == task->pid) {
    		cur_process = task->comm;
    		printk(KERN_INFO "##### TASK INFORMATION OF ''[%d] %s'' #####\n", cur_pid, cur_process);
			switch (task->state)
			{
			case 0:
				printk(KERN_INFO "- task state : Running or ready\n")
				break;
			case 1:
				printk(KERN_INFO "- task state : Wait with ignoring all signals\n")
				break;
			case 2:
				printk(KERN_INFO "- task state : Wait\n");
				break;
			case 3:
				printk(KERN_INFO "- task state : Stopped\n");
				break;
			default:
				break;
			}
		}
	}


    printk(KERN_INFO "- task state : ", );

	task->pid
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
