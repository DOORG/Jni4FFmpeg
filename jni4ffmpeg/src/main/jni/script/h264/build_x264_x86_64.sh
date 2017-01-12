#!/usr/bin/env bash
cd ./x264

 NDK=~/Library/Android/sdk/ndk-bundle
 TOOLCHAIN=${NDK}/toolchains/x86_64-4.9/prebuilt/darwin-x86_64
 PLATFORM=${NDK}/platforms/android-21/arch-x86_64
 PREFIX=../libx264/x86_64


./configure \
    --prefix=${PREFIX} \
    --enable-static \
    --enable-shared \
    --enable-pic \
    --disable-asm \
    --disable-cli \
    --host=x86_64-linux \
    --cross-prefix=${TOOLCHAIN}/bin/x86_64-linux-android- \
    --sysroot=${PLATFORM}

make clean
make -j8
make install

cd ..
