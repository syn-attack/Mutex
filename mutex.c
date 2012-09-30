/*
 * [ Let's play with mutex ]
 *
 * Author : Paulus Gandung Prakosa (syn-attack@devilzc0de.org)
 */

#ifdef __KERNEL__
#include <linux/kernel.h>
#endif
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/slab.h>

static int __init __self_module_loader(void) {
	struct mutex *mutex;
	int lock_status;
	int is_lock_acquired;

	mutex = kmalloc(sizeof(*mutex), GFP_KERNEL);
	if (unlikely(mutex == NULL)) {
		printk(KERN_ERR "Not enough memory to allocate.\n");
		return -1;
	}

	lock_status = mutex_is_locked(mutex);
	printk(KERN_INFO "Mutex status: %s.\n", (lock_status == 1) ? "locked" : "unlocked");

	if (likely(lock_status == 1)) {
		mutex_init(mutex);
	}

	lock_status = mutex_is_locked(mutex);
	printk(KERN_INFO "Mutex status: %s.\n", (lock_status == 1) ? "locked" : "unlocked");
	is_lock_acquired = mutex_trylock(mutex);

	if (likely(is_lock_acquired == 1)) {
		printk(KERN_INFO "Mutex has been acquired.\n");
		lock_status = mutex_is_locked(mutex);
		printk(KERN_INFO "Mutex status: %s.\n", (lock_status == 1) ? "locked" : "unlocked");
		mutex_unlock(mutex);
	}

	lock_status = mutex_is_locked(mutex);
	printk(KERN_INFO "Mutex status: %s.\n", (lock_status == 1) ? "locked" : "unlocked");

	kfree(mutex);

	return 0;
}

static void __exit __self_module_unloader(void) {
	printk(KERN_INFO "Overall process has been done.\n");

	return;
}

MODULE_LICENSE("GPL");

module_init(__self_module_loader);
module_exit(__self_module_unloader);