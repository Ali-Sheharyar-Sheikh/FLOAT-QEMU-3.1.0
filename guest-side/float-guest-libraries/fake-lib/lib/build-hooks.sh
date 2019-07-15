sudo gcc -c -g -fPIC hooks.c -o hooks.o
sudo gcc -shared -g -Wl,-soname,libhooks.so -o libhooks.so  hooks.o
sudo cp libhooks.so /usr/local/lib
sudo ldconfig
