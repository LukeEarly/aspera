#!/usr/bin/env bash

export PATH="$HOME/opt/cross/bin:$PATH" &&
export SYSROOT=`pwd`/build/sysroot &&
export CPPFLAGS=-D__debug &&
rm -rf build/isodir &&
mkdir -p build/sysroot &&
cd aspera &&
make clean &&
cd ../lib/a &&
make clean &&
cd ../../aspera &&
make install-headers &&
cd ../lib/a &&
make install-headers &&
make install-libs &&
cd ../../aspera &&
make install-multiboot &&
cd .. &&
#mkdir -p build/sysroot/boot/grub &&
#cp aspera/arch/i386/boot/multiboot/grub.cfg build/sysroot/boot/grub/grub.cfg &&

cd util/mkirfs &&
make &&
cd ../../initram &&
../util/mkirfs/mkirfs &&
cd .. &&
mv initram/irfs build/ &&
cp build/irfs build/sysroot/boot/irfs &&

grub-mkrescue -o build/aspera.iso build/sysroot
