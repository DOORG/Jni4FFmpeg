//
// Created by Doublemine on 2017/1/10.
//
#ifndef ANDROIDFFMPEG_ANDROID_LOG_H
#define ANDROIDFFMPEG_ANDROID_LOG_H
#include <android/log.h>

#define TAG "Doublemine"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)
#endif //ANDROIDFFMPEG_ANDROID_LOG_H
