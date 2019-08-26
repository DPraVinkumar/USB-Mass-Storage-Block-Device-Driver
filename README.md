# USB-Mass-Storage-Block-Device-Driver

Topics: 

--Developing USB device driver

--Developing mass storage device driver

--USB Specifications and protocol

--Developing a block device driver 

--Additionally, the driver can be mapped to learn SCSI drivers



	Topics in detail:

		-- Introduction

			Functional layers involved in USB memory device read and write operation.
			
				|------------------------------|	
				|            VFS               |
				|------------------------------|
				|         File system          |
				|------------------------------|
				|  Block Device sub-system     |
				|------------------------------|
				|      Block Device driver     |
				|------------------------------|
				|      USB Device driver       |
				|------------------------------|
				|          USB Core            |
				|------------------------------|
				|       UHCI Controller        |
				|------------------------------|
				
			
			--read/write call to USB device ==> VFS (Using System Call table and file inode).
			--VFS to actual filesystem on the USB memory device.
			--Filesystem to block device sub-system (takes care of I/O scheduling and organizing requests to increase opration efficiency)
			--Block device driver executes read/write call to USB device using USB device driver.
			--USB Device driver does not ineract to USB memory device directly, but it uses API and data structures provided by USB Core.
			
 -- Driver development setup

		As Linux kernel 2.6 already  has a USB mass storage driver, we need to remove that so that the new driver communicates with the device exclusively.	
			--Remove support for USB mass storage drvier.
			--recompile the Linux kernel.
			--Use this modified kernel.

-- Understanding USB devices

                |---------------------------------------------|
                |                         __________________  |
                |                         |  ____________   | |
                |                         | | Endpoint   |  | |
                |                         | |____________|  | |
                |                         | | Endpoint   |  | |
                |                         | |____________|  | |
                |                         |                 | |
                |                         |  Interface      | |
		|                         |_________________| |
                |                         __________________  |
                |                         |  ____________   | |
                |                         | | Endpoint   |  | |
                |                         | |____________|  | |
                |                         | | Endpoint   |  | |
                |                         | |____________|  | |
                |                         |                 | |
                |                         |  Interface      | |
		|                         |_________________| |
                |                                             |
                | Configuration                               |
		|---------------------------------------------|

			A USB device contains 

			An interface contains one or more endpoints. The endpoints are like unidirectional pipes which carry commands or data from host to device and vice-versa.

			. Control endpoint - These endpoints are used to configure and control the device. Every USB device has at least one control endpoint.
			. Bulk endpoint - These endpoints are used to carry large data to/from the device reliably.
			  For example, USB pen drives have two bulk endpoints for IN and OUT directions respectively.
			. Interrupt endpoints - These endpoints are used to carry small data with higher priority.
			  For example, USB keyboards and mouse have such endpoints.
			. Isochronous endpoint - These enndpoints are used to carry large data without reliability.
			  For Example, USB webcam have such endpoints.
			
			Most of the USB memory devices have at least 1 Control endpoint and 2 Bulk endpoint(1 bulk-IN, 1 bulk-OUT).	
