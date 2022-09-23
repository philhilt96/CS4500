#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

int print_self_init_module(void) {
    struct task_struct *task = current;

    // Display current process info
    printk(KERN_INFO "Current Process Name:\t%s\n", task->comm);
    printk(KERN_INFO "Current Process ID:\t\t%d\n", task->pid);
    printk(KERN_INFO "Current Process State:\t%d (UPDATE THIS TO STRING STATE)\n", task->state);

    // Move to current's parent process
    task = task->parent;
   
    // Display all parent processes until init
    while (task != &init_task) {
	printk(KERN_INFO "Parent Process Name:\t\t%s\n", task->comm);
	printk(KERN_INFO "Parent Process ID:\t\t%d\n", task->pid);
	printk(KERN_INFO "Parent Process State:\t%d (UPDATE TO STRING)\n", task->state);

	// Update task pointer
	task = task->parent;
    }
 
    // Success
    return 0;
}

void print_self_cleanup_module(void) {
    printk(KERN_INFO "Cleanup print_self. Goodbye!\n");
}

module_init(print_self_init_module);
module_exit(print_self_cleanup_module);

MODULE_LICENSE("GPL");
