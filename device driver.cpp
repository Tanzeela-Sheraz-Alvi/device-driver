#include<Linux/module.h>
#include ‹Linux/kernel.h>
#include < linux/usb.h›
#include ‹Linux/video.h>
#include ‹Linux/uvcvideo.h›
#define VENDOR_ID 0x22d9
#define PRODUCT_ID 0x276a
static struct usb_device *device;
static int cam_probe(struct usb_ interface *interface, const struct usb_device_id *id)
printk(KERN_INFO "Mobile Camera: Device Connected\n");
// Register with UVC driver
device = interface_to_usbdev (interface) ;
// Attempt to bind with UVC Video Driver
if (usb_match_id(interface, id)) {
printk(KERN_INFO "Mobile Camera: Attempting UVC binding\n");
} else {
printk(KERN_ERR "Mobile Camera: UVC binding failed\n");
return -ENODEV;
}
return 0;
}
static void cam_disconnect (struct usb_interface *interface)
{
printk (KERN_INFO "Mobile. Camera: Device Disconnected\n) 
}
static struct usb_device_id cam_tablel] = {
{
(USE DEVICE VENDOR_ TD, PRODUCT ID) },
{}
};
 MODULE_DEVICE_TABLE (usb, cam_table) ;
 static struct usb_driver cam_ driver = {

.name        ="mobile_cam",

.id_table     =cam_table,
.probe         =cam_probe,
.disconnect     =cam_disconnect,
 };
 static int_init cam_init (void)
{
return usb_register (&cam_driver) ;
}
 static void__exit cam_exit(void)
{
usb _deregister (&cam_driver);
}
 module_ init (cam init.) ;
 module_exit(cam_exit);
