CFILES += MyDeviceModule.c vector.c dict.c
obj-m += rubik.o
rubik-objs := $(CFILES:.c=.o)
ccflags-y += -std=gnu99 -Wall -Wno-declaration-after-statement
all:
	make -C /home/lapla/kernel-hack/kernelhack/linux-6.2.12 M=$(shell pwd) modules
clean:
	rm -f *.o *.ko *.mod *.mod.c Module.symvers modules.order
rwtest:
	gcc testrw.c -o rw
ioctl:
	gcc testioctl.c -o ioctl
