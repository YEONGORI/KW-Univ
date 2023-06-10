#ifndef FTRACEHOOKING_H
#define FTRACEHOOKING_H

#define __NR_ftrace 336
#define BUFF_SIZE 1024

#include <linux/unistd.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>

#include <asm/syscall_wrapper.h>

#endif