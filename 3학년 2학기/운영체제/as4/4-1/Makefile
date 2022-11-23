obj-m := file_varea.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc -o assin4 test.c
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
