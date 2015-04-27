#!/bin/sh

git clone git://nbd.name/luci2/libubox.git libubox
cd libubox
mkdir build
cd build
cmake ..
make ubox
sudo mkdir -p /usr/local/include/libubox
sudo cp ../*.h /usr/local/include/libubox
sudo cp libubox.so /usr/local/lib
sudo ldconfig

cd ../..

git clone git://nbd.name/uci.git uci
cd uci
mkdir build
cd build

CFLAGS=-I../../
LDFLAGS=-L../../libubox/build/
export CFLAGS
export LDFLAGS

cmake ..
make uci cli
sudo make install
sudo ldconfig
