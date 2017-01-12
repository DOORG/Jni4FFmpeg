#!/usr/bin/env bash
cd ./x264

 NDK=~/Library/Android/sdk/ndk-bundle
 TOOLCHAIN=${NDK}/toolchains/mipsel-linux-android-4.9/prebuilt/darwin-x86_64
 PLATFORM=${NDK}/platforms/android-14/arch-mips
 PREFIX=../libx264/mips


./configure \
    --prefix=${PREFIX} \
    --enable-static \
    --enable-shared \
    --enable-pic \
    --disable-asm \
    --disable-cli \
    --host=mipsel-linux \
    --cross-prefix=${TOOLCHAIN}/bin/mipsel-linux-android- \
    --sysroot=${PLATFORM}

make clean
make -j8
make install

cd ..
