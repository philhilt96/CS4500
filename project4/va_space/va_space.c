#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/mm_types.h>

// get pid from user provided argument
int pid = 1677;
module_param(pid, int, 0);

int va_space_init_mod(void){
    // pid and vm structs
    struct task_struct *task;
    struct mm_struct *mm;
    struct vm_area_struct *all_vmas;
    struct vm_area_struct current_vma;
    // variable declarations
    int vmaCount = 0;
    int count = 0;
    int totalSize = 0;
    unsigned long start = 0;
    // get memory descriptor and set current vma
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    mm = task->mm;
    all_vmas = mm->mmap;
    vmaCount = mm->map_count;
    current_vma = *all_vmas;
    start = current_vma.vm_start;
    // loop through all vma in provided process
    printk("%i Number of Virtual Memory Areas", vmaCount);
    for (current_vma = *all_vmas; count < vmaCount; count++) {
        printk("=======================\n");
        printk("VMA #%i Start Address: 0x%lx\n", count+1, current_vma.vm_start);
        printk("VMA #%i End Address: 0x%lx\n", count+1, current_vma.vm_end);
        printk("VMA #%i Total Size: 0x%lx\n", count+1, current_vma.vm_end - current_vma.vm_start); 
        // increment total size and move to next vma
        totalSize += (current_vma.vm_end - current_vma.vm_start);
        if (count != vmaCount -1) {
	    current_vma = *(current_vma.vm_next);
        }
    }
    // print result
    printk("=======================\n");
    printk("Total VMA Size Bytes: %i\n", totalSize);
    printk("Total VMA Size Kbytes: %i\n", totalSize/(1 << 10));

    return 0;
}

void va_space_cleanup_mod(void){
    printk(KERN_INFO "Cleanup va_space. Goodbye!\n");
}

module_init(va_space_init_mod);
module_exit(va_space_cleanup_mod);

MODULE_LICENSE("GPL");
