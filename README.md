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
