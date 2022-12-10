#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <linux/highmem.h>

// Gather user input pid and va
int pid = 1647;
char* va = "400000";
module_param(pid, int, 0);
module_param(va, charp, 0);

int va_status_mod_init(void) {
    // declare necessary variables
    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *ptep, pte;
    
    // cast virtual address string to unsigned long
    unsigned long address;
    kstrtoul(va, 16, &address);

    // init task struct
    struct task_struct *task;
    struct mm_struct *mm;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    mm = task->mm;

    // determine page global directory
    pgd = pgd_offset(mm, address);
    if (pgd_none(*pgd) || pgd_bad(*pgd))
	return -1;

    // determine page upper directory
    pud = pud_offset(pgd, address);
    if (pud_none(*pud) || pud_bad(*pud))
	return -1;

    // determine page middle directory
    pmd = pmd_offset(pud, address);
    if (pmd_none(*pmd) || pmd_bad(*pmd))
	return -1;

    spinlock_t *lock;
    ptep = pte_offset_map_lock(mm, pmd, address, &lock);
    pte = *ptep;

    // check if page table entry exists
    if (!pte_present(pte)) {
	printk(KERN_INFO "Address %s in in disk\n", va);
    }
    else {
	printk(KERN_INFO "Address %s is in memory\n", va);
    }

    pte_unmap_unlock(ptep, lock);
    return 0;
}

void va_status_mod_cleanup(void) {
    printk(KERN_INFO "Cleanup va_status. Goodbye!\n");
}

module_init(va_status_mod_init);
module_exit(va_status_mod_cleanup);

MODULE_LICENSE("GPL");
