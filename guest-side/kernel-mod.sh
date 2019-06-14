cd '/home/vm-cuda10/Downloads/ivshmem-guest-code-master/kernel_module/uio'

sudo modprobe uio
sudo insmod uio_ivshmem.ko
sudo chmod 777 /dev/vport0p1
sudo chmod 777 /dev/uio0

