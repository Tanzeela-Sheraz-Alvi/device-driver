#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "laptop_camera"
#define BUF_LEN 80

static int major_number;
static char message[BUF_LEN] = "Camera Device is ready\n";
static struct class *camera_class = NULL;
static struct device *camera_device = NULL;

static int dev_open(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "laptop Camera Driver Opened\n");
    return 0;
}

static ssize_t dev_read(struct file *filep , char *buffer , size_t len , loff_t *offset){
    int bytes_read = strlen(message);
    if(len < bytes_read)
        bytes_read = len;
    if(copy_to_user(buffer, message, bytes_read))
        return -EFAULT;
    return bytes_read;
}

static int dev_release(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "laptop Camera Driver Closed\n");
    return 0;
}

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .release = dev_release,
};

static int __init camera_init(void){
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Camera driver failed to register\n");
        return major_number;
    }

    camera_class = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(camera_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(camera_class);
    }

    camera_device = device_create(camera_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(camera_device)) {
        class_destroy(camera_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(camera_device);
    }

    printk(KERN_INFO "Camera driver registered successfully\n");
    return 0;
}

static void __exit camera_exit(void){
    device_destroy(camera_class, MKDEV(major_number, 0));
    class_destroy(camera_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "laptop Camera Driver Removed\n");
}
