#include <jni.h>
#include <string>
#include "BasicPlayer/BasicPlayer.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_app_basicplayer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    BasicPlayer basicPlayer("");
    return env->NewStringUTF(hello.c_str());
}
