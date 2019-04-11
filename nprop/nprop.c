#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <android/log.h>
#include <sys/system_properties.h>

#define TAG "nprop--->"

char* getprop(char *key) {
    static char val[PROP_VALUE_MAX];
    __system_property_get(key, val);
    return val;
}

int main()
{
    // char sdk[PROP_VALUE_MAX];
    // __system_property_get("ro.build.version.sdk", sdk);

    printf("sdk=        %s\n", getprop("ro.build.version.sdk"));
    printf("hardware=   %s\n", getprop("ro.hardware"));
    printf("device=     %s\n", getprop("ro.product.device"));
    printf("brand=      %s\n", getprop("ro.product.brand"));
    printf("model=      %s\n", getprop("ro.product.model"));
    printf("name=       %s\n", getprop("ro.product.name"));
    printf("user=       %s\n", getprop("ro.build.user"));

    return 0;
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeProp_prop(JNIEnv *env, jclass obj, jstring packageName)
{
    __android_log_print(ANDROID_LOG_INFO, TAG, "into prop");

    __android_log_print(ANDROID_LOG_DEBUG, TAG, "sdk=        %s", getprop("ro.build.version.sdk"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "hardware=   %s", getprop("ro.hardware"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "device=     %s", getprop("ro.product.device"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "brand=      %s", getprop("ro.product.brand"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "model=      %s", getprop("ro.product.model"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "name=       %s", getprop("ro.product.name"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "user=       %s", getprop("ro.build.user"));
}
