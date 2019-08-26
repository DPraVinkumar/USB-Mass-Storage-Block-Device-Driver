/* FILE: usb_core.h */
/*Author: "PraVin <pravinkumar.dhende@gmail.com>"*/

#ifndef _USB_CORE_H_
#define _USB_CORE_H_
struct usbdev_private {
	struct usb_device *udev;
};
#define TRACE(arg...) printk(arg)
#define LOG_MSG(arg...) printk(arg)
#endif


