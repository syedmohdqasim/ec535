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
#include <linux/gpio.h>
#include <linux/gpio/consumer.h> /* gpio access */

MODULE_LICENSE("Dual BSD/GPL");

#define GPIO_BUTTON0 26

/* GPIO pins
- red light: gpio67
- yellow light: gpio68
- green light: gpio44
- button0: gpio26
- button1: gpio46
*/

// fasync interrupt -> when button pressed aka when file gpio26/value [button0] changes
// timer cycle every second executing the light 

static void mytraffic_exit(void);
static int mytraffic_init(void);
static ssize_t mytraffic_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
static ssize_t mytraffic_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static int mytraffic_fasync(int fd, struct file *filp, int mode);
static int mode;
//static ssize_t list();
static struct timer_list * etx_timer;
static struct timer_list * mode_timer;
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

/* GPIO pins
- red light: gpio67
- yellow light: gpio68
- green light: gpio44
- button0: gpio26
- button1: gpio46
*/

static struct gpio leds_gpios[] = {
        { 67, GPIOF_OUT_INIT_LOW, "Red LED" }, /*default to OFF*/
        { 68, GPIOF_OUT_INIT_LOW,  "Yellow LED" }, /*default to OFF*/
        { 44, GPIOF_OUT_INIT_LOW,  "Green LED"   } /*default to OFF*/
};

static struct gpio buttons_gpios[] = {
        { 26, GPIOF_IN, "Button 0" }, /*default to OFF*/
        { 46, GPIOF_IN,  "Button 1" }, /* default to OFF */
};

/* global variables */
static int mytraffic_major = 61; // major number

static int count;  // counter for light duration
static int mode; // traffic light mode
static int time_in_ms=1000;
static unsigned bite=256;

static unsigned capacity = 256;  
static char *mytraffic_buff; //buffer to store data
static int mytraffic_len; //length of data in buffer

static void my_timer_callback(struct timer_list * data)
{
    // if (async_queue)
    //     kill_fasync(&async_queue, SIGIO, POLL_IN);


    
    printk(KERN_ALERT " NORMAL MODE \n");
    

    if(mode ==0 )
        printk(KERN_ALERT " NORMAL MODE \n");
    else if(mode ==1)
        printk(KERN_ALERT " RED FLASH MODE \n");
    else
        printk(KERN_ALERT " YELLOW FLASH MODE \n");

    gpio_set_value(44, 1);

    mod_timer(etx_timer, jiffies + msecs_to_jiffies(time_in_ms));

}

static void mode_timer_callback(struct timer_list * data)
{
    // if (async_queue)
    //     kill_fasync(&async_queue, SIGIO, POLL_IN);

    int value1 = gpio_get_value(26);
    
    printk(KERN_ALERT " look for button and change mode.: %d \n",value1);

    mod_timer(mode_timer, jiffies + msecs_to_jiffies(time_in_ms/10));
    
}

static int my_timer_set(int time_in_ms, const char *msg)
{
    if(timer_pending(etx_timer)==0)
    { timer_setup(etx_timer, my_timer_callback, 0); 
    
    }
    mod_timer(etx_timer, jiffies + msecs_to_jiffies(time_in_ms));
    

    return 0;
}

static int mode_timer_set(int time_in_ms, const char *msg)
{
    if(timer_pending(etx_timer)==0)
    { timer_setup(etx_timer, my_timer_callback, 0); 
    
    }
    mod_timer(mode_timer, jiffies + msecs_to_jiffies(time_in_ms/10));
    

    return 0;
}

static int my_timer_update(int time_in_ms, const char *msg)
{
    mod_timer(etx_timer, jiffies + msecs_to_jiffies(time_in_ms));
  
    return 0;
}


static int mytraffic_init(void)
{

    int result = register_chrdev(mytraffic_major, "mytraffic", &mytraffic_ops);
    if (result < 0)
    {
        goto fail;
    }
    
    int err = gpio_request_array(leds_gpios, ARRAY_SIZE(leds_gpios));
    if (err){
        goto fail;
    }
    
    int err2 = gpio_request_array(buttons_gpios, ARRAY_SIZE(buttons_gpios));
    if (err2){
        goto fail;
    }


    mytraffic_buff = kmalloc(capacity*3, GFP_KERNEL); 
    if (!mytraffic_buff)
    { 
    printk(KERN_ALERT "Insufficient kernel memory\n"); 
    result = -ENOMEM;
    goto fail; 
    } 
    memset(mytraffic_buff, 0, capacity*3);
    mytraffic_len = 0;

    etx_timer = kmalloc(sizeof(struct timer_list), GFP_KERNEL);
    timer_setup(etx_timer, my_timer_callback, 0);
    mod_timer(etx_timer, jiffies + msecs_to_jiffies(time_in_ms));

    mode_timer = kmalloc(sizeof(struct timer_list), GFP_KERNEL);
    timer_setup(mode_timer, mode_timer_callback, 0);
    mod_timer(mode_timer, jiffies + msecs_to_jiffies(time_in_ms/10));

    return 0;

fail:
    mytraffic_exit();
    return result;
}

static void mytraffic_exit(void)
{
    unregister_chrdev(mytraffic_major, "mytraffic");
    if (mytraffic_buff)
    {
    kfree(mytraffic_buff);
    }
    gpio_free_array(leds_gpios, ARRAY_SIZE(leds_gpios));
    gpio_free_array(buttons_gpios, ARRAY_SIZE(buttons_gpios));

}

/*
    When button 0 is pressed, switch modes
    When button 1 is pressed, pedestrian call (additional feature)
    When both are pressed simulatenously, lightbulb check/reset (extra credit)
*/

static int mytraffic_fasync(int fd, struct file *filp, int mode) {
    return fasync_helper(fd, filp, mode, &async_queue);
}

/* Read character device returns: 
        current operational mode
        current cycle rate
        current status of each light
        whether or not a pedestrian is present (additional feature)
*/

static ssize_t mylist(void){
	char tbufL[capacity*3], *tbptrL = tbufL;
	int i = 0;
	tbufL[0] = '\0'; //clear buffer
	switch(mode){
		case 0:
			tbptrL += sprintf(tbptrL, "Mode: NORMAL\n");
		case 1:
			tbptrL += sprintf(tbptrL, "Mode: FLASHING YELLOW\n");
		case 2:
			tbptrL += sprintf(tbptrL, "Mode: FLASHING RED\n");
	}
	tbptrL += sprintf(tbptrL, "Cycle rate: %dHZ\n", 1); //TODO set 1 to a variable
	tbptrL += sprintf(tbptrL, "R:%d Y:%d G:%d\n",gpio_get_value(67), gpio_get_value(68), gpio_get_value(44));
	//tbptrL += sprintf(tbptrL, "Pedestrian: Present\n"); 
	return (sprintf(mytraffic_buff, "%s", tbufL));
}

static ssize_t mytraffic_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{   
    mytraffic_len = mylist();
    if (*f_pos >= mytraffic_len)
    {
    return 0;
    }

    /* do not go over then end */
    if (count > mytraffic_len - *f_pos)
    count = mytraffic_len - *f_pos;

    /* do not send back more than a bite */
    if (count > bite) count = bite;

    /* Transfering data to user space */ 
    if (copy_to_user(buf, mytraffic_buff + *f_pos, count))
    {
    return -EFAULT;
    }

    *f_pos += count;
    return count; 
}

/* Additional feature: Writable character device, writing an integer to character
device alters the cycle rate of the traffic light, anythng else should be ignored */

static ssize_t mytraffic_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    return count;
}
