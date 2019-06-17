cd '/lib/modules/4.15.0-20-generic/kernel/drivers/uio'

sudo modprobe uio
sudo insmod uio_ivshmem.ko
sudo chmod 777 /dev/vport0p1
sudo chmod 777 /dev/uio0

