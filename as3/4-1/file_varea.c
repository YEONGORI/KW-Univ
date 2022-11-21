#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/unistd.h>

#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/sched/mm.h>
#include <linux/syscalls.h>
#include <asm/syscall_wrapper.h>

#define __NR_ftrace 336

// typedef asmlinkage long (*real_sys)(const struct pt_regs *regs);
// static real_sys *syscall_table;
// real_sys real_ftrace; 

typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);
static sys_call_ptr_t *syscall_table;
sys_call_ptr_t real_process_tracer;

static asmlinkage pid_t file_varea(const struct pt_regs *regs);

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

// static int __init hooking_init(void)
// {
//    syscall_table = (real_sys*) kallsyms_lookup_name("sys_call_table");

//    make_rw(syscall_table);
//    real_ftrace = syscall_table[__NR_ftrace];
//    syscall_table[__NR_ftrace] = (real_sys)file_varea;

//    return 0;
// }

static int __init hooking_init(void)
{
	syscall_table = (sys_call_ptr_t *)kallsyms_lookup_name("sys_call_table");

	make_rw(syscall_table);
	real_process_tracer = syscall_table[__NR_ftrace];
	syscall_table[__NR_ftrace] = (sys_call_ptr_t)file_varea;

	return 0;
}

static void __exit hooking_exit(void)
{
	syscall_table[__NR_ftrace] = real_process_tracer;
	make_ro(syscall_table);
}

static asmlinkage pid_t file_varea(const struct pt_regs *regs)
{
   pid_t process_id = regs->di;
   struct task_struct *_task = pid_task(find_vpid(process_id), PIDTYPE_PID);
   struct mm_struct *mm = get_task_mm(_task);
   struct vm_area_struct *mmap = mm->mmap;

   // char *_buf = kmalloc(1024, GFP_KERNEL);
   char _buf[1000];
   char *_path = NULL;

   printk(KERN_INFO "######## Loaded files of a process 'assin4(%d)' in VM ########\n", process_id);

   while (mmap->vm_next)
   {
      struct file *_file = mmap->vm_file;
      if (_file)
      {
         memset(_path, 0, 1024);
         _path = d_path(&_file->f_path, _buf, 1024);
         printk(KERN_INFO "mem[%lx~%lx] code[%lx~%lx] data[%lx~%lx] heap[%lx~%lx] %s\n", mmap->vm_start, mmap->vm_end, mm->start_code, mm->end_code, mm->start_data, mm->end_data, mm->start_brk, mm->brk, _path);
      }

      mmap = mmap->vm_next;
   }

   // do{
   //    file = mmap->vm_file;
   //    memset(buf, 0, 1024);

   //    if(file){
   //       path = d_path(&file->f_path, buf, 1024);   
   //       printk(KERN_INFO "mem[%lx~%lx] code[%lx~%lx] data[%lx~%lx] heap[%lx~%lx] %s\n", mmap->vm_start, mmap->vm_end, mm->start_code, mm->end_code, mm->start_data, mm->end_data, mm->start_brk, mm->brk, path);
   //    }
   //    mmap = mmap->vm_next;
   // }while(mmap!=NULL);

   printk(KERN_INFO "################################################################\n");
   return process_id;
};

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");