LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg
LOCAL_SRC_FILES := libffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE := jni4ffmpeg
#LOCAL_SRC_FILES := FFmpegHelper.c FFmpegHelper.h ffmpeg.c ffmpeg.h ffmpeg_opt.c cmdutils.c cmdutils.h ffmpeg_filter.c cmdutils_common_opts.h
LOCAL_SRC_FILES := native4ffmpeghelper.c native4ffmpeghelper.h ffmpeg.c ffmpeg.h ffmpeg_opt.c cmdutils.c cmdutils.h ffmpeg_filter.c cmdutils_common_opts.h
# 这里的地址改成自己的 FFmpeg 源码目录
LOCAL_C_INCLUDES := /Users/doublemine/Desktop/FFMPEG/ffmpeg-2.8.10
LOCAL_LDLIBS := -llog -lz -ldl
#LOCAL_LDLIBS := -llog -ljnigraphics -lz -ldl -lgcc -lm
LOCAL_SHARED_LIBRARIES := ffmpeg
include $(BUILD_SHARED_LIBRARY)