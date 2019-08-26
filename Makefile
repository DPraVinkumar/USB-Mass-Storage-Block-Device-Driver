obj-m += usb.o
usb-objs := usb_core.o
CFLAGS_task09.o := -DDEBUG
KSDIR ?= /lib/modules/`uname -r`/build

all:
	make -C $(KSDIR) M=$(PWD) modules

clean:
	make -C $(KSDIR) M=$(PWD) clean
