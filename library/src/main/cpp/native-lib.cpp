
#include <jni.h>

extern "C" {
#include "ffmpeg.h"

JNIEXPORT jstring JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_getAvCodec(JNIEnv *env, jclass type) {


    return env->NewStringUTF(avcodec_configuration());
}

JNIEXPORT jint JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_run(JNIEnv *env, jclass type, jint argc,
                                                     jobjectArray args) {

    // TODO

}
}