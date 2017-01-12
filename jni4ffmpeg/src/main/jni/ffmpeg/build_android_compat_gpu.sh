#!/bin/bash
sh build_x264_arm.sh
echo ================================================
echo Build h264 completed!
echo ================================================
export TMPDIR=~/Desktop/ffmpegtemp #这句很重要，不然会报错 unable to create temporary file in
NDK=~/Library/Android/sdk/ndk-bundle
PLATFORM=${NDK}/platforms/android-14/arch-arm
TOOLCHAIN=${NDK}/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64
function build_one
{
./configure \
    --prefix=${PREFIX} \
    --target-os=linux \
    --cross-prefix=${TOOLCHAIN}/bin/arm-linux-androideabi- \
    --arch=arm \
    --sysroot=${PLATFORM} \
    --extra-cflags="-I$PLATFORM/usr/include" \
    --cc=${TOOLCHAIN}/bin/arm-linux-androideabi-gcc \
    --nm=${TOOLCHAIN}/bin/arm-linux-androideabi-nm \
    --disable-shared \
    --enable-runtime-cpudetect \
    --enable-gpl \
    --enable-small \
    --enable-cross-compile \
    --disable-debug \
    --enable-static \
    --disable-doc \
    --disable-asm \
    --disable-ffmpeg \
    --disable-ffplay \
    --disable-ffprobe \
    --disable-ffserver \
    --enable-postproc \
    --enable-avdevice \
    --disable-symver \
    --disable-stripping \
    --enable-gpl \
    --enable-version3 \
    --enable-small \
    --enable-encoders \
    --enable-libx264 \
    --enable-encoder=libx264 \
    --enable-muxers \
    --enable-muxer=mov \
    --enable-muxer=ipod \
    --enable-muxer=psp \
    --enable-muxer=mp4 \
    --enable-muxer=avi \
    --enable-decoders \
    --enable-decoder=aac \
    --enable-decoder=aac_latm \
    --enable-decoder=h264 \
    --enable-decoder=mpeg4 \
    --enable-demuxers \
    --enable-demuxer=h264 \
    --enable-demuxer=mov \
    --enable-parsers \
    --enable-parser=aac \
    --enable-parser=ac3 \
    --enable-parser=h264 \
    --enable-protocol=file \
    --enable-protocol=rtmp \
    --enable-bsf=aac_adtstoasc \
    --enable-bsf=h264_mp4toannexb \
    --enable-zlib\
     --extra-cflags=${EXTRA_CFLAGS} \
    --extra-ldflags=${EXTRA_LDFLAGS}
${ADDITIONAL_CONFIGURE_FLAG}
sed -i '' 's/HAVE_LRINT 0/HAVE_LRINT 1/g' config.h
sed -i '' 's/HAVE_LRINTF 0/HAVE_LRINTF 1/g' config.h
sed -i '' 's/HAVE_ROUND 0/HAVE_ROUND 1/g' config.h
sed -i '' 's/HAVE_ROUNDF 0/HAVE_ROUNDF 1/g' config.h
sed -i '' 's/HAVE_TRUNC 0/HAVE_TRUNC 1/g' config.h
sed -i '' 's/HAVE_TRUNCF 0/HAVE_TRUNCF 1/g' config.h
sed -i '' 's/HAVE_CBRT 0/HAVE_CBRT 1/g' config.h
sed -i '' 's/HAVE_RINT 0/HAVE_RINT 1/g' config.h
make clean
make -j4
make install
${TOOLCHAIN}/bin/arm-linux-androideabi-ld \
-rpath-link=${PLATFORM}/usr/lib \
-L${PLATFORM}/usr/lib \
-L${PREFIX}/lib \
-soname libffmpeg.so -shared -nostdlib -Bsymbolic --whole-archive --no-undefined -o \
${PREFIX}/libffmpeg.so \
 ${EXTRA_DIR}/lib/libx264.a \
    libavcodec/libavcodec.a \
    libavfilter/libavfilter.a \
    libswresample/libswresample.a \
    libavformat/libavformat.a \
    libavutil/libavutil.a \
    libswscale/libswscale.a \
    libpostproc/libpostproc.a \
    libavdevice/libavdevice.a \
    -lc -lm -lz -ldl -llog --dynamic-linker=/system/bin/linker \
    ${TOOLCHAIN}/lib/gcc/arm-linux-androideabi/4.9.x/libgcc.a
}
CPU=armv7-a
OPTIMIZE_CFLAGS="-mfloat-abi=softfp -mfpu=vfp -marm -march=$CPU "
PREFIX=../libbuild/single
ADDITIONAL_CONFIGURE_FLAG=


EXTRA_DIR=libx264/armeabi
# 加入x264编译库
EXTRA_CFLAGS="-I./${EXTRA_DIR}/include "
EXTRA_LDFLAGS="-L./${EXTRA_DIR}/lib"

build_one

echo ================================================
echo Build FFmpeg completed!
echo ================================================