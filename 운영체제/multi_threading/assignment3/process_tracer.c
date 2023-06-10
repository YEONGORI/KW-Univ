// every code including wrapping
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/unistd.h>
#include <linux/string.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <linux/init_task.h>
#include <asm/syscall_wrapper.h>

#define __NR_ftrace 336

int fork_count, sibling_count, child_count;
pid_t cur_pid = 0;

char *cur_process;

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);
static sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_process_tracer;

static asmlinkage pid_t process_tracer(const struct pt_regs *regs);

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
	real_process_tracer = syscall_table[__NR_ftrace];
	syscall_table[__NR_ftrace] = (sys_call_ptr_t)process_tracer;

	return 0;
}

static void __exit hooking_exit(void)
{
	syscall_table[__NR_ftrace] = real_process_tracer;
	make_ro(syscall_table);
}

static asmlinkage pid_t process_tracer(const struct pt_regs *regs)
{
    struct task_struct *cur_task, *par_task;
	struct task_struct *sibling_task, *child_task;
	struct list_head *sibling_list, *child_list;

	for_each_process(cur_task) {
		if (regs->di == cur_task->pid) {
			par_task = cur_task->real_parent;
    		cur_pid = regs->di;
    		cur_process = cur_task->comm;
			sibling_count = 0;
			child_count = 0;
    		printk(KERN_INFO "##### TASK INFORMATION OF ''[%d] %s'' #####\n", cur_pid, cur_process);

			switch (cur_task->state)
			{
			case 0:
				printk(KERN_INFO "- task state : Running or ready\n");
				break;
			case 1:
				printk(KERN_INFO "- task state : Wait with ignoring all signals\n");
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


			printk(KERN_INFO "- Number of context switches : %d\n", (int)(cur_task->nvcsw + cur_task->nivcsw));


			printk(KERN_INFO "- Number of calling fork() : %d\n", cur_task->fork_count);


			printk(KERN_INFO "- it's parent process : [%d] %s\n", par_task->pid, par_task->comm);


			printk(KERN_INFO "- it's sibling process(es) : \n");
			list_for_each(sibling_list, &cur_task->children) {
				sibling_task = list_entry(sibling_list, struct task_struct, sibling);
				if (sibling_task->pid != cur_task->pid) {
					printk(KERN_INFO "\t> [%d] %s\n", sibling_task->pid, sibling_task->comm);
					sibling_count++;
				}
			}
			if (sibling_count)
				printk(KERN_INFO "\t> This process has %d sibling process(es)\n", sibling_count);
			else
				printk(KERN_INFO "\t> It has no sibling.\n");


			printk(KERN_INFO "- it's child process(es) : \n");
			list_for_each(child_list, &cur_task->children) {
				child_task = list_entry(child_list, struct task_struct, sibling);
				if (child_task->pid != cur_task->pid) {
					printk(KERN_INFO "\t> [%d] %s\n", child_task->pid, child_task->comm);
					child_count++;
				}
			}
			if (child_count)
				printk(KERN_INFO "\t> This process has %d child process(es)\n", child_count);
			else
				printk(KERN_INFO "\t> It has no child.\n");


			printk(KERN_INFO "##### END OF INFORMATION #####\n");
			return (regs->di);
		}
	}
	return (-1);
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");
