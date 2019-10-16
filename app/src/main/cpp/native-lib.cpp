#include "jni.h"
#include "android/log.h"
//#include "../head/more.h"
#include <stdio.h>
jstring  test(JNIEnv* env,jclass ,jstring name){
    const char* name_char=env->GetStringUTFChars(name,JNI_FALSE);
    __android_log_print(ANDROID_LOG_ERROR,"22m","name : %s",name_char);
    return env->NewStringUTF("zengzeming");
}

const  char* classPathName="com/zzm/more/MainActivity";
const JNINativeMethod methods[]={
        { "test","(Ljava/lang/String;)Ljava/lang/String;",(void*)test }
};
int registerNativeMethods(JNIEnv* env, const char* className, const JNINativeMethod* gMethods,int numMethods){
    jclass clazz;
    clazz=env->FindClass(className);
    if(clazz==NULL){
        __android_log_print(ANDROID_LOG_ERROR,"22m","native registration unable to find class '%s'",className);
        return  JNI_FALSE;
    }
    if(env->RegisterNatives(clazz,gMethods,numMethods)<0){
        __android_log_print(ANDROID_LOG_ERROR,"22m","RegisterNatives failed for  '%s'",className);
        return  JNI_FALSE;
    }
    return JNI_TRUE;
}

int registerNatives(JNIEnv* env){
    if(!registerNativeMethods(env,classPathName,methods, sizeof(methods)/ sizeof(methods[0]))){
        return  JNI_FALSE;
    }
    return JNI_TRUE;
}

typedef  union {
    JNIEnv* env;
    void* venv;
}UnionJNIEnvToVoid;

jint  JNI_OnLoad(JavaVM* vm, void* ) {
    UnionJNIEnvToVoid uenv;
    uenv.venv = NULL;
    jint result = -1;
    JNIEnv *env = NULL;
    __android_log_print(ANDROID_LOG_ERROR, "22m", "JNI_OnLoad");
    if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "22m", "ERROR: GetEnv failed");
        goto fail;
    }
    env = uenv.env;
    if (registerNatives(env) != JNI_TRUE) {
        __android_log_print(ANDROID_LOG_ERROR, "22m", "ERROR: registerNatives failed");
        goto fail;
    }
    result = JNI_VERSION_1_6;
    fail:
    return result;
}