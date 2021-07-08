#!/bin/bash

SAVEDPATH=$PATH
export PATH=/opt/opendingux-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/bin:/opt/opendingux-toolchain/usr/bin:/opt/opendingux-toolchain/usr/sbin:$PATH
make -f Makefile.dingux && pushd ./bin && ./make_opk.sh && popd
export PATH=$SAVEDPATH
