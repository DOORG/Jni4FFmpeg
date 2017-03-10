//
// Created by doublemine on 17/1/18.
//

#ifndef JNI4FFMPEG_CHECK_ENV_H

#define JNI4FFMPEG_CHECK_ENV_H

#include <jni.h>
#include <sys/system_properties.h>
#include <sys/time.h>
#include "android_log.h"
#include <time.h>
#include "stdlib.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
bool check_status(long unix_time);

long get_current_time();


long get_end_time_point();


void check_env_status();

void call_convert_date(JNIEnv *env);
#ifdef __cplusplus
}
#endif

#endif //JNI4FFMPEG_CHECK_ENV_H
