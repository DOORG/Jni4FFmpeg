#!/usr/bin/env bash
cd ./x264

 NDK=~/Library/Android/sdk/ndk-bundle
 TOOLCHAIN=${NDK}/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64
 PLATFORM=${NDK}/platforms/android-21/arch-arm64
 PREFIX=../libx264/armeabi_v8a


./configure \
    --prefix=${PREFIX} \
    --enable-static \
    --enable-shared \
    --enable-pic \
    --disable-asm \
    --disable-cli \
    --host=aarch64-linux \
    --cross-prefix=${TOOLCHAIN}/bin/aarch64-linux-android- \
    --sysroot=${PLATFORM}

make clean
make -j8
make install

cd ..
