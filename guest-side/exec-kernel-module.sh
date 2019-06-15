#!/bin/sh

# Ivshmem kernel module already compiled and placed in this following directory
# cd into the directory and manually insert the ivshmem kernel module
cd /lib/modules/4.15.0-36-generic/kernel/drivers/uio

# Manually insert ivshmem module in kernel
sudo modprobe uio
sudo insmod uio_ivshmem.ko

# Change permission on devices
sudo chmod 777 /dev/uio0
sudo chmod 777 /dev/vport0p1
