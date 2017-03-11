#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>

#define READ_MESSAGE	"Hello ThundeRatz!\n"

static ssize_t hello_thunderatz_read(struct file *filp, char __user *buffer,
	size_t length, loff_t *ppos)
{
	return simple_read_from_buffer(buffer, length, ppos, READ_MESSAGE,
		sizeof(READ_MESSAGE));
}

static const struct file_operations hello_thunderatz_fops = {
	.owner = THIS_MODULE,
	.read  = hello_thunderatz_read,
};

static struct miscdevice hello_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "hello_thunderatz",
	.fops = &hello_thunderatz_fops
};

static int __init hello_init(void)
{
	int retval;

	pr_debug("hello_thunderatz: init\n");

	retval = misc_register(&hello_device);
	if (retval)
		pr_err("hello_thunderatz: misc_register %d\n", retval);
	return retval;
}

static void __exit hello_exit(void)
{
	pr_debug("hello_thunderatz: exit\n");

	misc_deregister(&hello_device);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tiago Koji Castro Shibata <tishi@linux.com>");
MODULE_DESCRIPTION("ThundeRatz hello module");
