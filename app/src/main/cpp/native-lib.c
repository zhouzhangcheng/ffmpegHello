#include <jni.h>
#include <stdio.h>
#include <android/log.h>

#include "include/libavcodec/avcodec.h"
#include "include/libavfilter/avfilter.h"
#include "include/libavformat/avformat.h"

#define LOGE(format, ...) __android_log_print(ANDROID_LOG_ERROR,"(>_<)",format,##__VA_ARGS__)

struct URLProtocol;

/*extern "C"*/
JNIEXPORT
jstring
Java_com_example_administrator_helloworld_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject obj) {
    char info[4000] = {0}; // 全部初始化为0 ，结束符
    av_register_all();

    struct URLProtocol *pup = NULL;

    struct URLProtocol **p_temp = &pup;

    avio_enum_protocols((void **) p_temp, 0);

    while ((*p_temp) != NULL) {
        sprintf(info, "%s[in][%10s]\n", info, avio_enum_protocols((void **) p_temp, 0));
    }
    pup = NULL;
    avio_enum_protocols((void **) p_temp, 1);

    while ((*p_temp) != NULL) {
        sprintf(info, "%s[out][%10s]\n", info, avio_enum_protocols((void **) p_temp, 1));
    }

    return (*env)->NewStringUTF(env, info);
}
