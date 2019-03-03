#include <linux/init.h>
#include <linux/module.h>
#include <linux/init.h>
//static int hello_data __initdata=3; //frees memory
static int __init hello_init(void){
	printk(KERN_INFO "Hello world \n");
	return 0;
}
static void __exit hello_exit(void){
	printk(KERN_INFO "Bye!");
}
module_init(hello_init); //__init starts code(when not a module)
module_exit(hello_exit); //__exit cleans up
MODULE_LICENSE("GPL");
