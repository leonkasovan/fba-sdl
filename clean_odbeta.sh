#!/bin/bash
SAVEDPATH=$PATH
export PATH=/opt/lepus-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/bin:/opt/gcw0-toolchain/usr/bin:/opt/gcw0-toolchain/usr/sbin:$PATH
make -f Makefile.dingux DEVICE=gcw0 clean
rm -f bin/fbasdl_gcw0.dge
export PATH=$SAVEDPATH

SAVEDPATH=$PATH
export PATH=/opt/lepus-toolchain/usr/mipsel-lepus-linux-musl/sysroot/usr/bin:/opt/lepus-toolchain/usr/bin:/opt/lepus-toolchain/usr/sbin:$PATH
make -f Makefile.dingux DEVICE=lepus clean
rm -f bin/fbasdl_lepus.dge
rm -f bin/*.opk
export PATH=$SAVEDPATH
