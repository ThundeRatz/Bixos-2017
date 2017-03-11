KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
CFLAGS_hello_thunderatz.o := -DDEBUG
obj-m += hello_thunderatz.o
.PHONY: all clean

all:
	make -C ${KERNEL_DIR} M=$(PWD) modules

clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean
