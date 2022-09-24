#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

// Function to return string state given input long int state
char* state_string(long state) {
    switch (state) {
	case -1:
	    return "UNRUNNABLE";
	case 0:
	    return "TASK_RUNNING";
	case 1:
	    return "TASK_INTERRUPTIBLE";
	case 2:
	    return "TASK_UNINTERRUPTIBLE";
	case 4:
	    return "TASK_STOPPED";
	case 8:
	    return "TASK_TRACED";
	case 16:
	    return "EXIT_ZOMBIE";
	case 32:
	    return "EXIT_DEAD";
	case 64:
	    return "TASK_NONINTERACTIVE";
    }
    return "NON_DEFINED";
}

int print_self_init_module(void) {
    struct task_struct *task = current;

    // Display current process info
    printk(KERN_INFO "Current Process Name:\t%s\n", task->comm);
    printk(KERN_INFO "Current Process ID:\t\t%d\n", task->pid);
    printk(KERN_INFO "Current Process State:\t%s\n", state_string(task->state));

    // Move to current's parent process
    task = task->parent;
   
    // Display all parent processes until init
    while (task != &init_task) {
	printk(KERN_INFO "Parent Process Name:\t\t%s\n", task->comm);
	printk(KERN_INFO "Parent Process ID:\t\t%d\n", task->pid);
	printk(KERN_INFO "Parent Process State:\t%s\n", state_string(task->state));

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
