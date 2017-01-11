#include "native4ffmpeghelper.h"
#include "Android_log.h"
#include "ffmpeg.h"
#include <stdlib.h>
#include <stdbool.h>

JNIEXPORT jint JNICALL Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_run
        (JNIEnv *env, jobject obj, jint argc, jobjectArray args) {
    int i = 0;
    char **argv = NULL;
    jstring *strr = NULL;

    if (args != NULL) {
        argv = (char **) malloc(sizeof(char *) * argc);
        strr = (jstring *) malloc(sizeof(jstring) * argc);

        for (i = 0; i < argc; ++i) {
            strr[i] = (jstring) (*env)->GetObjectArrayElement(env, args, i);
            argv[i] = (char *) (*env)->GetStringUTFChars(env, strr[i], 0);
            LOGD("FFmpeg args: %s", argv[i]);
        }

    }

    LOGD("Execute commands: %s", *argv);
    int result = run(argc, argv);
    if (result == 0) {
        LOGI("Execute success.");
    }
    else {
        LOGE("Execute failed. exit with code=%d", result);
    }
    for (i = 0; i < argc; ++i) {
        (*env)->ReleaseStringUTFChars(env, strr[i], argv[i]);
    }
    free(argv);
    free(strr);
    return result;

}


JNIEXPORT jint JNICALL
Java_work_wanghao_jni4ffmpeg_LibavHelper_run(JNIEnv *env, jclass type, jobjectArray commands) {

    // TODO


}

JNIEXPORT jstring JNICALL
Java_work_wanghao_jni4ffmpeg_Native4FFmpegHelper_getAvCodec(JNIEnv *env, jclass type) {

    // TODO
    char info[10000] = {0};
    sprintf(info, "%s\n", avcodec_configuration());
    return (*env)->NewStringUTF(env, info);
}