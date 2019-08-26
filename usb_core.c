/*FILE: usb_core.c*/
/*Author: "PraVin <pravinkumar.dhende@gmail.com>"*/

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/usb.h>
#include<linux/slab.h>
#include "usb_core.h"

#define USB_PEN_DRIVE_VID 0x0f5f
#define USB_PEN_DRIVE_PID 0x1325
#define USB_KINGSTON_VID 0x0951
#define USB_KINGSTON_DT_PID 0x1602
#define USB_KINGSTON_4G_PID 0x1607


#define USB_SONY_VID 0x054c
#define USB_SONY_PID 0x05ba

struct usbdev_private *p_usb_dev_info;

static int device_info(struct usb_interface* interface)
{
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;

	unsigned char epAddr, epAttr;
	/* Setup the endpoint information*/
	/* checout the end points */
	iface_desc = &interface->altsetting[0]; /* XXX */
	printk("No. of altsetting = %d\n",interface->num_altsetting);
	printk("No. of endpoints = %d\n",iface_desc->desc.bNumEndpoints);
	return 0;
}


static int usbdev_probe(struct usb_interface *interface, const struct usb_device_id *usb_device_id)
{
	TRACE("<1>usbdev_probe ENTRY\n");
	p_usb_dev_info = kmalloc(sizeof(struct usbdev_private), GFP_KERNEL);
	
	if(!p_usb_dev_info)
		return -1;
  	memset(p_usb_dev_info, 0, sizeof(struct usbdev_private));
	p_usb_dev_info->udev = interface_to_usbdev(interface);
	usb_get_dev(p_usb_dev_info->udev);
	if(device_info(interface))
	{
		kfree(p_usb_dev_info);
		return -1;	
	}
	return 0;
}

static void usbdev_disconnect(struct usb_interface *interface)
{
	TRACE("usbdev_disconnect called\n");
	usb_put_dev(p_usb_dev_info->udev);
	return;
}

/*table of devices that work with this driver */

static struct usb_device_id usbdev_table [] = {
	{ USB_DEVICE(USB_PEN_DRIVE_VID, USB_PEN_DRIVE_PID) },
	{ USB_DEVICE(USB_KINGSTON_VID, USB_KINGSTON_DT_PID) },
	{ USB_DEVICE(USB_KINGSTON_VID, USB_KINGSTON_4G_PID) },
	{ USB_DEVICE(USB_SONY_VID, USB_SONY_PID) },


};

static struct usb_driver usbdev_driver = {
	name: "usbdev",
	probe: usbdev_probe,
	disconnect: usbdev_disconnect,
	id_table: usbdev_table
};

int init_module(void)
{
	usb_register(&usbdev_driver);
	return 0;
}

void cleanup_module(void)
{
	usb_deregister(&usbdev_driver);
	return;
}

MODULE_LICENSE("GPL");


