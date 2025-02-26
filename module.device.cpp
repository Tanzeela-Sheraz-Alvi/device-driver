
module_init(camera_init);
module_exit(camera_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux driver for a laptop's built-in camera.");obj-m += camera_driver.o
