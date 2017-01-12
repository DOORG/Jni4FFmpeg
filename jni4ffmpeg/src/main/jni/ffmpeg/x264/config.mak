SRCPATH=.
prefix=../libx264/armeabi
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
libdir=${exec_prefix}/lib
includedir=${prefix}/include
SYS_ARCH=ARM
SYS=LINUX
CC=/Users/doublemine/Library/Android/sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc
CFLAGS=-Wno-maybe-uninitialized -Wshadow -O3 -ffast-math  -Wall -I. -I$(SRCPATH) --sysroot=/Users/doublemine/Library/Android/sdk/ndk-bundle/platforms/android-14/arch-arm -std=gnu99 -D_GNU_SOURCE -fPIC -fomit-frame-pointer -fno-tree-vectorize
COMPILER=GNU
COMPILER_STYLE=GNU
DEPMM=-MM -g0
DEPMT=-MT
LD=/Users/doublemine/Library/Android/sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc -o 
LDFLAGS= --sysroot=/Users/doublemine/Library/Android/sdk/ndk-bundle/platforms/android-14/arch-arm -lm  -ldl
LIBX264=libx264.a
AR=/Users/doublemine/Library/Android/sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc-ar rc 
RANLIB=/Users/doublemine/Library/Android/sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc-ranlib
STRIP=/Users/doublemine/Library/Android/sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-strip
INSTALL=install
AS=
ASFLAGS= -I. -I$(SRCPATH) -DSTACK_ALIGNMENT=4 -DPIC -DHIGH_BIT_DEPTH=0 -DBIT_DEPTH=8
RC=
RCFLAGS=
EXE=
HAVE_GETOPT_LONG=1
DEVNULL=/dev/null
PROF_GEN_CC=-fprofile-generate
PROF_GEN_LD=-fprofile-generate
PROF_USE_CC=-fprofile-use
PROF_USE_LD=-fprofile-use
HAVE_OPENCL=yes
SOSUFFIX=so
SONAME=libx264.so.148
SOFLAGS=-shared -Wl,-soname,$(SONAME)  -Wl,-Bsymbolic
default: lib-shared
install: install-lib-shared
default: lib-static
install: install-lib-static
LDFLAGSCLI = 
CLI_LIBX264 = $(LIBX264)
