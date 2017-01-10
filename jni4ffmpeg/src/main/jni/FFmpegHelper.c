//
// Created by Doublemine on 2017/1/10.
//
#include <stdio.h>
#include "ffmpeg.h"
#include "FFmpegHelper.h"
#include "libavcodec/avcodec.h"
/*
 * Class:     work_wanghao_jni4ffmpeg_LibavHelper
 * Method:    exec
 * Signature: ([Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_work_wanghao_jni4ffmpeg_LibavHelper_exec
  (JNIEnv *env, jclass obj, jobjectArray commands)
  {
    LOGD("get argc=%s",avcodec_configuration());
    int argc = (*env)->GetArrayLength(env, commands);
    char *argv[argc];
    int i;

  //  for (i = 0; i < argc; i++) {
    //    jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
      //  LOGD("parser js");
        //argv[i] = (char*) (*env)->GetStringUTFChars(env, js, 0);
   // }
    LOGD("exec run");
    return run(argc, "ffmpeg");

  }