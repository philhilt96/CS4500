#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>

// Variable to get PID command line argument
int arbitrary_process = 3;
module_param(arbitrary_process, int, 0);

int print_other_init_module(void) {
    struct task_struct *task;
    
    // Get PID provided in command line argument
    task = pid_task(find_vpid(arbitrary_process), PIDTYPE_PID);
    
    // Make sure PID was provided
    if (task == NULL)
    {
	printk(KERN_INFO "Cannot find that process PID\n");
	return 1;
    }

    // Display current process info
    printk(KERN_INFO "Current Process Name:\t%s\n", task->comm);
    printk(KERN_INFO "Current Process ID:\t\t%d\n", task->pid);
    printk(KERN_INFO "Current Process State:\t%ld (UPDATE THIS TO STRING STATE)\n", task->state);

    // Move to current's parent process
    task = task->parent;
   
    // Display all parent processes until init
    while (task != &init_task) {
	printk(KERN_INFO "Parent Process Name:\t\t%s\n", task->comm);
	printk(KERN_INFO "Parent Process ID:\t\t%d\n", task->pid);
	printk(KERN_INFO "Parent Process State:\t%ld (UPDATE TO STRING)\n", task->state);

	// Update task pointer
	task = task->parent;
    }
 
    // Success
    return 0;
}

void print_other_cleanup_module(void) {
    printk(KERN_INFO "Cleanup print_other. Goodbye!\n");
}

module_init(print_other_init_module);
module_exit(print_other_cleanup_module);

MODULE_LICENSE("GPL");
