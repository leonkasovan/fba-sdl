#!/bin/bash

SAVEDPATH=$PATH
export PATH=/opt/lepus-toolchain/usr/mipsel-lepus-linux-musl/sysroot/usr/bin:/opt/lepus-toolchain/usr/bin:/opt/lepus-toolchain/usr/sbin:$PATH
make -f Makefile.dingux DEVICE=lepus && pushd ./bin && ./make_opk_lepus.sh && popd
export PATH=$SAVEDPATH
