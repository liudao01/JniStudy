//
// Created by liudao on 12/8/20.
//

#ifndef JNISTUDY_LOGUTIL_H
#define JNISTUDY_LOGUTIL_H

#include <android/log.h>

#include <sys/time.h>

#define  LOG_TAG "JNILIB"

#define LOG_DEBUG true //日志开关，true为开，其它为关

#define  LOGE(...)   __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGV(...)  if(LOG_DEBUG) __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  if(LOG_DEBUG) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  if(LOG_DEBUG) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

#define ByteFlowPrintE LOGCATE
#define ByteFlowPrintV LOGCATV
#define ByteFlowPrintD LOGCATD
#define ByteFlowPrintI LOGCATI

#define FUN_BEGIN_TIME(FUN) {\
    LOGE("%s:%s func start", __FILE__, FUN); \
    long long t0 = GetSysCurrentTime();

#define FUN_END_TIME(FUN) \
    long long t1 = GetSysCurrentTime(); \
    LOGE("%s:%s func cost time %ldms", __FILE__, FUN, (long)(t1-t0));}

#define BEGIN_TIME(FUN) {\
    LOGE("%s func start", FUN); \
    long long t0 = GetSysCurrentTime();

#define END_TIME(FUN) \
    long long t1 = GetSysCurrentTime(); \
    LOGE("%s func cost time %ldms", FUN, (long)(t1-t0));}

static long long GetSysCurrentTime()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    long long curTime = ((long long)(time.tv_sec))*1000+time.tv_usec/1000;
    return curTime;
}

#define GO_CHECK_GL_ERROR(...)   LOGE("CHECK_GL_ERROR %s glGetError = %d, line = %d, ",  __FUNCTION__, glGetError(), __LINE__)

#define DEBUG_LOGCATE(...) LOGE("DEBUG_LOGCATE %s line = %d",  __FUNCTION__, __LINE__)

#endif //JNISTUDY_LOGUTIL_H
