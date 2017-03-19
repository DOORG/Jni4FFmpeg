#include <string>
#include <jni.h>

extern "C"
{
#include <libavcodec/avcodec.h>


JNIEXPORT jstring JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_run(JNIEnv *env, jclass type, jint argc,
                                                     jobjectArray args) {
    char buff[100];
    snprintf(buff, sizeof(buff), "ffmpeg %s", "Hello");
    std::string buffAsStdStr = buff;

}

JNIEXPORT jstring JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_getAvCodec(JNIEnv *env, jclass type) {


    return env->NewStringUTF(avcodec_configuration());
}
}
