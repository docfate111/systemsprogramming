
obj-m += passargs.o
obj-m += startstop.o
startstop-objs := start.o stop.o

KDIR = /usr/src/linux-headers-4.15.0-45-generic

all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order
