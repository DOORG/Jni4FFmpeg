#!/usr/bin/env bash
cd ./x264

 NDK=~/Library/Android/sdk/ndk-bundle
 TOOLCHAIN=${NDK}/toolchains/x86-4.9/prebuilt/darwin-x86_64
 PLATFORM=${NDK}/platforms/android-14/arch-x86
 PREFIX=../libx264/x86


./configure \
    --prefix=${PREFIX} \
    --enable-static \
    --enable-shared \
    --enable-pic \
    --disable-asm \
    --disable-cli \
    --host=i686-linux \
    --cross-prefix=${TOOLCHAIN}/bin/i686-linux-android- \
    --sysroot=${PLATFORM}

make clean
make -j8
make install

cd ..
