#!/bin/sh

MAJOR_VERSION="3"
MINOR_VERSION="1.11"

VERSION=${MAJOR_VERSION}.${MINOR_VERSION}


if [ ! -e nettle-${VERSION}.tar.gz ]
then
wget https://ftp.gnu.org/gnu/nettle/nettle-${VERSION}.tar.gz
fi

tar xvf  nettle-${VERSION}.tar.xz
cd nettle-${VERSION}
./configure
make
sudo make install


