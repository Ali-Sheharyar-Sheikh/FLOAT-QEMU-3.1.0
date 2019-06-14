gcc -c -fPIC hooks.c -o hooks.o
gcc -shared -Wl,-soname,libhooks.so -o libhooks.so  hooks.o
sudo cp libhooks.so /usr/local/lib
make
g++ -g -w -pg -fPIC -Wall -c -I/usr/local/cuda/include transfer-virtio-serial.c -o transfer-virtio-serial.o
g++ -g -w -pg -fPIC -Wall -c -I/usr/local/cuda/include -M transfer-virtio-serial.c > .transfer-virtio-serial.d
g++ -shared -Wl,-soname,libfacuvirser.so.0 -o libfacuvirser.so.0.0.1 virtCudaLib.o transfer-virtio-serial.o
sudo make reinstall