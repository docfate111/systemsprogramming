#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thelford Williams");
//parameters from console:
static short int myshort=1;
static int myint=333;
static long int mylong=9393;
static char* mystring="String";
static int myintArray[2]={7, 3};
static int arr_argc=0;
/*module_param(parameters name, data type, number, permission)
*/
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short int"); //description
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");
//register (macro) module_param(name_var, type, permissions)
//Permissions: S_I(R/W/X)(USR/GRP)
//R-read, W-write, X-execute
//USR-user, GRP-group
static int hello_init(void){
	int i;
	printk(KERN_INFO "Hello, world 5\n=============\n");
	printk(KERN_INFO "myshort is a short integer: %hd\n", myshort);
	printk(KERN_INFO "myint is an integer: %d\n", myint);
	printk(KERN_INFO "mylong is a long integer: %ld\n", mylong);
	printk(KERN_INFO "mystring is a string: %s\n", mystring);
	for (i = 0; i < (sizeof myintArray / sizeof (int)); i++)
	{
		printk(KERN_INFO "myintArray[%d] = %d\n", i, myintArray[i]);
	}
	printk(KERN_INFO "got %d arguments for myintArray.\n", arr_argc);
	return 0;
	return 0;
}
static void hello_exit(void){
	printk(KERN_INFO "Bye!");
}
module_init(hello_init);
module_exit(hello_exit);
