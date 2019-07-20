//
// Created by 周杰 on 2019-07-20.
//

#include "include/Hello.h"

#include <jni.h>
#include <assert.h>

jstring test(JNIEnv *env, jobject obj)
{
    return env->NewStringUTF("Hello is jay jni test.");
}

static const char *jniClassName = "com/jay/jnitest/MainActivity";
static JNINativeMethod methods[] = {
        {"test", "()Ljava/lang/String;", (void*)test},
};

static int registerNatives(JNIEnv* env) {
    jclass clazz = env->FindClass(jniClassName);
    if (clazz == NULL)
        return JNI_FALSE;

    jint methodSize = sizeof(methods) / sizeof(methods[0]);
    if ( env->RegisterNatives(clazz, methods, methodSize) < 0 )
        return JNI_FALSE;

    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    //注册方法
    if (!registerNatives(env))
        return JNI_ERR;

    result = JNI_VERSION_1_6;
    return result;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    jint ret = vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    if (ret != JNI_OK) {
        return ;
    }
}