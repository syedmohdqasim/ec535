/* Necessary includes for device drivers */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/system_misc.h> /* cli(), *_flags */
#include <linux/uaccess.h>
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
#include <linux/seq_file.h>
#include <linux/gpio/consumer.h> /* gpio access */

MODULE_LICENSE("Dual BSD/GPL");


/* GPIO pins
- red light: gpio67
- yellow light: gpio68
- green light: gpio44
- button0: gpio26
- button1: gpio46
*/

// fasync interrupt -> when button pressed aka when file gpio26/value [button0] changes
// timer cycle every second executing the light 


/* declarations */
static void mytraffic_exit(void);
static int mytraffic_init(void);
static ssize_t mytraffic_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
static ssize_t mytraffic_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static int mytraffic_fasync(int fd, struct file *filp, int mode);
// static int mytraffic_open(struct inode *inode, struct file *filp);
// static int mytraffic_release(struct inode *inode, struct file *filp);

module_init(mytraffic_init);
module_exit(mytraffic_exit);

/* file operations */
static struct file_operations mytraffic_ops = {
	//open: mytraffic_open,
	//release: mytraffic_release,
	write: mytraffic_write,
	read: mytraffic_read,
	fasync: mytraffic_fasync
};


static struct fasync_struct *async_queue;

/* global variables */
static int mytraffic_major = 61; // major number
static int count;  // counter for light duration
static int mode; // traffic light mode


static int mytraffic_init(void)
{

    /* Registering device */
    result = register_chrdev(mytraffic_major, "mytraffic", &mytraffic_ops);
    if (result < 0)
    {
        return result;
    }

    return 0;

fail:
    mytraffic_exit();
    return result;
}

static void mytraffic_exit(void)
{
    /* Freeing the major number */
    unregister_chrdev(mytraffic_major, "mytraffic");
}

static int mytraffic_fasync(int fd, struct file *filp, int mode) {
    return fasync_helper(fd, filp, mode, &async_queue);
}

static ssize_t mytraffic_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    return count;
}

static ssize_t mytraffic_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    return count;
}
