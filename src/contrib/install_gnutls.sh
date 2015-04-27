#!/bin/sh

MAJOR_VERSION="3.3"
MINOR_VERSION="9"

VERSION=${MAJOR_VERSION}.${MINOR_VERSION}


if [ ! -e gnutls-${VERSION}.tar.xz ]
then
wget http://ftp.heanet.ie/mirrors/ftp.gnupg.org/gcrypt/gnutls/v$MAJOR_VERSION/gnutls-${MAJOR_VERSION}.${MINOR_VERSION}.tar.xz
fi

tar xvf  gnutls-${VERSION}.tar.xz
cd gnutls-${VERSION}
./configure
make
sudo make install


