#!/bin/bash

SAVEDPATH=$PATH
export PATH=/opt/opendingux-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/bin:/opt/opendingux-toolchain/usr/bin:/opt/opendingux-toolchain/usr/sbin:$PATH
make -f Makefile.dingux clean
rm -f bin/fbasdl.dge
export PATH=$SAVEDPATH
