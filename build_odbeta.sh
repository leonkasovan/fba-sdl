#!/bin/bash
SAVEDPATH=$PATH
export PATH=/opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/bin:/opt/gcw0-toolchain/usr/bin:/opt/gcw0-toolchain/bin:$PATH
export TOOLCHAIN_DIR=/opt/gcw0-toolchain/usr/bin/
export TOOLCHAIN_PREFIX=mipsel-gcw0-linux-uclibc-
make -f Makefile.dingux DEVICE=gcw0
make -f Makefile.dingux DEVICE=gcw0 clean
export PATH=$SAVEDPATH

SAVEDPATH=$PATH
export PATH=/opt/lepus-toolchain/usr/mipsel-lepus-linux-musl/sysroot/usr/bin:/opt/lepus-toolchain/usr/bin:/opt/lepus-toolchain/bin:$PATH
export TOOLCHAIN_DIR=/opt/lepus-toolchain/usr/bin/
export TOOLCHAIN_PREFIX=mipsel-lepus-linux-musl-
make -f Makefile.dingux DEVICE=lepus && pushd ./bin && ./make_opk.sh && popd
export PATH=$SAVEDPATH
unset TOOLCHAIN_DIR
unset TOOLCHAIN_PREFIX
