//
// Created by doublemine on 17/1/18.
//


#include "check_env.h"

#ifdef __cplusplus
extern "C" {
#endif
long get_current_time() {
    return time(NULL);
}

/* Return current time in milliseconds */
static double now_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000. + tv.tv_usec / 1000.;
}

/**
 *  return false when out of date
 */
bool check_status(long unix_time) {
    return unix_time >= get_current_time();
}


long get_end_time_point() {
    /*2017/5/31 21:56:21*/
    return 1496238981;
}


void check_env_status() {
    if (!check_status(get_end_time_point())) {
        exit(0);
    }
}


void call_convert_date(JNIEnv *env) {
    jclass native_lib_class = env->FindClass("work/wanghao/jni4ffmpeg/LibavHelper");
    if (native_lib_class == NULL) {
        LOGE("can not load the module==work/wanghao/jniffmpeg/LibavHelper");
        env->DeleteLocalRef(native_lib_class);
        return;
    }
    jmethodID convert_unix2string = env->GetStaticMethodID(native_lib_class, "convert2String",
                                                           "(J)Ljava/lang/String;");
    if (convert_unix2string == NULL) {
        LOGE("can not find method id==convert2String");
        env->DeleteLocalRef(native_lib_class);
        return;
    }
    LOGD("call the method");

    jobject result = env->CallStaticObjectMethod(native_lib_class, convert_unix2string,
                                                 get_current_time());
    if (result == NULL) {
        LOGE("call the method return NULL");
        env->DeleteLocalRef(native_lib_class);
        env->DeleteLocalRef(result);
        return;
    }

    jboolean is_copy;

    const char *c_str = env->GetStringUTFChars((jstring) result, &is_copy);

    LOGE("result=%s", c_str);

    env->DeleteLocalRef(native_lib_class);
    env->DeleteLocalRef(result);
}
#ifdef __cplusplus
}
#endif







