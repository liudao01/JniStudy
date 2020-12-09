#include <jni.h>
#include <string>

//#include "util/LogUtil.h"
//#include "util/AndroidLog.h"
//#include "include/LogUtil.h"
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_open_jnistudy_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */thiz) {
//    LOGCATE("GetFFmpegVersion\n%s", "strBuffer");
//    如果是c程序，要用 (*env)->
//    如果是C++要用 env->
    //定义一个C++语言字符串 注意导入了<string> 库
    std::string hello = "Hello from C++";
//    LOGD("GetFFmpegVersion\n%s", "test");
    __android_log_print(ANDROID_LOG_ERROR, "jnilib", "The value of 1 + 1 is %d", 1 + 1);

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_open_jnistudy_MainActivity_accessField(JNIEnv *env, jobject thiz) {
//    LOGD("GetFFmpegVersion\n%s", "test");
//    LOGCATE("GetFFmpegVersion\n%s", "strBuffer");
    //得到jclass
    jclass jclz = env->GetObjectClass(thiz);

    /*反射：Class （反射的入口）
	  反射：Field （成员变量）
	  反射：Method （成员方法）*/
    //fieldID 属性名称
    //牛逼啊 现在都android studio 自动给带出来了 "Ljava/lang/String;"   以前还需要自己写
    jfieldID jfieldId = env->GetFieldID(jclz, "key", "Ljava/lang/String;");
    //得到key对应的值
    /* 获取java中str的值 */
    jstring jstr = (jstring) env->GetObjectField(thiz, jfieldId);

//    LOGCATD("测试下打印");

//    LOGD("android jni 打印")
    /* 将jstring转化为char */
    char *cstr = (char *) env->GetStringUTFChars(jstr, NULL);

    /* 修改值 */
    char newstr[20] = "world!";
    strcat(newstr, cstr);

    /* 将char转成jstring */
    jstring jstrnew = env->NewStringUTF(newstr);

    /* 重新设置到java类变量里面去 */
    env->SetObjectField(thiz, jfieldId, jstrnew);

    /* 释放JNI层资源 */
    env->ReleaseStringUTFChars(jstr, cstr);

    return jstrnew;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_open_jnistudy_MainActivity_accessStaticField(JNIEnv *env, jobject jobj) {
//    LOGD("GetFFmpegVersion\n%s", "test");
//    LOGCATE("GetFFmpegVersion\n%s", "strBuffer");
    //得到jclass
    jclass jclz = env->GetObjectClass(jobj);

    //fieldId 属性名称, 属性签名
    jfieldID fid = env->GetStaticFieldID(jclz, "count", "I");

    jint count = env->GetStaticIntField(jclz, fid);
    count = count + 10;

    //最后设置进去
    env->SetStaticIntField(jclz, fid, count);
    return nullptr;
}

/**
 * 调用java 非静态方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_open_jnistudy_MainActivity_accessMethod(JNIEnv *env, jobject thiz) {
//    LOGD("GetFFmpegVersion\n%s", "test");
//    LOGCATE("GetFFmpegVersion\n%s", "strBuffer");
    //获取jclass
    jclass jclz = env->GetObjectClass(thiz);
    if (NULL == jclz) {
        printf("jclz == null");
    }
    //jmethodId
    //方法的名字 方法的签名
    jmethodID mid = env->GetMethodID(jclz, "getRandeomInt", "(I)I");

    if (NULL == mid) {
        printf("mid == null");
    }
    //调用java的方法
    jint random = env->CallIntMethod(thiz, mid, 100);
    if (NULL == random) {
        printf("randow == null");
    }
    printf("C random: %d \n", random);

}










