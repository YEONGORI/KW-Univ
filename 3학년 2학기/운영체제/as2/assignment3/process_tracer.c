// every code including wrapping
#include "sched.h"

int fork_count, sibling_count, child_count;
pid_t cur_pid = 0;

char *cur_process;

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);
static sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_process_tracer;

static asmlinkage pid_t process_tracer(pid_t trace_task);

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
    struct task_struct *cur_task, *par_task;
	struct task_struct *sibling_task, *child_task;
	struct list_head *list;

	for_each_process(task) {
		if (trace_task == task->pid) {
			cur_task = current;
			par_task = task->real_parent
    		cur_pid = trace_task;
    		cur_process = task->comm;
			sibling_count = 0;
			child_count = 0;
    		printk(KERN_INFO "##### TASK INFORMATION OF ''[%d] %s'' #####\n", cur_pid, cur_process);

			switch (cur_task->state)
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
			case 4:
				printk(KERN_INFO "- task state : Stopped\n");
				break;
			case 32:
				printk(KERN_INFO "- task state : Zombie process\n");
				break;
			case 128:
				printk(KERN_INFO "- task state : Dead\n");
				break;
			default:
				printk(KERN_INFO "- task state : etc.\n");
				break;
			}

			printk(KERN_INFO "- Process Group Leader: [%d] %s\n", cur_task->pid, cur_task->comm);


			printk(KERN_INFO "- Number of context switches : %d\n", (cur_task->nvcsw + cur_task->nivcsw));


			printk(KERN_INFO "- Number of calling fork() : %d\n", cur_task->fork_count);


			printk(KERN_INFO "- it's parent process : [%d] %s\n", par_task->pid, par_process->comm);


			printk(KERN_INFO "- it's sibling process(es) : \n");
			list_for_each_entry(sibling_task, &par_task->children, list) {
				sibling_count++;
				printk(KERN_INFO "\t> [%d] %s\n", sibling_task->pid, sibling_task->comm);
			}
			if (sibling_count)
				printk(KERN_INFO "\t> This process has %d sibling process(es)\n", sibling_count);
			else
				printk(KERN_INFO "\t> It has no sibling.\n");


			printk(KERN_INFO "- it's child process(es) : \n");
			list_for_each_entry(child_task, &cur_task->children, list) {
				child_count++;
				printk(KERN_INFO "\t> [%d] %s\n", child_task->pid, child_task->comm)
			}
			if (child_count)
				printk(KERN_INFO "\t> This process has %d child process(es)\n", child_count);
			else
				printk(KERN_INFO "\t> It has no child.\n");


			printk(KERN_INFO "##### END OF INFORMATION #####\n");
			return (trace_task);
		}
	}
	return (-1);
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
