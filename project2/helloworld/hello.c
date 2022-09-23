#include <linux/module.h>
#include <linux/kernel.h>


int init_mod(void){
	printk(KERN_INFO "Hello world!\n");
	return 0;
}

void cleanup_mod(void){
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(init_mod);
module_exit(cleanup_mod);

MODULE_LICENSE("GPL");
