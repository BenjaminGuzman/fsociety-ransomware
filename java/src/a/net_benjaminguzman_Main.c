#include <jni.h> // JNI header provided by JDK
#include <stdio.h>
#include "net_benjaminguzman_Main.h"

JNIEXPORT void JNICALL Java_net_benjaminguzman_Main_a(JNIEnv *, jclass) {
    printf("Hello World!\n");
    return;
}