#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <android/log.h>
#include <sys/system_properties.h>

#include "inlineHook.h"

#define TAG "nhook--->"

int (*old_prop)(const char *) = NULL;
static bool is_hook = false;

char* getprop(char *key) {
    static char val[PROP_VALUE_MAX];
    __system_property_get(key, val);
    return val;
}

int new_prop(const char *key, char *value)
{
    char *newvalue;
    if(strcmp(key, "ro.build.version.sdk") == 0) {
        newvalue = "26";
        memcpy(value, newvalue, strlen(newvalue));
    } else if(strcmp(key, "ro.hardware") == 0) {
        newvalue = "ExoticFruit";
    } else {
        newvalue = "others";
        memcpy(value, newvalue, strlen(newvalue));
    }
    return 0;
}

int hookProp()
{
    if (!is_hook) {
        if (registerInlineHook((uint32_t) __system_property_get, (uint32_t) new_prop, (uint32_t **) &old_prop) != ELE7EN_OK) {
            return -1;
        }
        if (inlineHook((uint32_t) __system_property_get) != ELE7EN_OK) {
            return -1;
        }
        is_hook = true;
        return 0;
    } else {
        __android_log_print(ANDROID_LOG_WARN, TAG, "is hooked!");
        return -2;
    }
}

int unHookProp()
{
    if (is_hook) {
        if (inlineUnHook((uint32_t) __system_property_get) != ELE7EN_OK) {
            return -1;
        }
        is_hook = false;
        return 0;
    } else {
        __android_log_print(ANDROID_LOG_WARN, TAG, "is not hook!");
        return -2;
    }
}

int main()
{
    printf("sdk=        %s\n", getprop("ro.build.version.sdk"));
    printf("hardware=   %s\n", getprop("ro.hardware"));
    printf("device=     %s\n", getprop("ro.product.device"));
    printf("brand=      %s\n", getprop("ro.product.brand"));
    printf("model=      %s\n", getprop("ro.product.model"));
    printf("name=       %s\n", getprop("ro.product.name"));
    printf("user=       %s\n", getprop("ro.build.user"));

    printf("==========hook==========\n");
    hookProp();
    printf("sdk=        %s\n", getprop("ro.build.version.sdk"));

    printf("==========unhook==========\n");
    unHookProp();
    printf("sdk=        %s\n", getprop("ro.build.version.sdk"));

    return 0;
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeHook_prop(JNIEnv *env, jclass obj, jstring packageName)
{
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "into prop");

    __android_log_print(ANDROID_LOG_DEBUG, TAG, "sdk=        %s", getprop("ro.build.version.sdk"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "hardware=   %s", getprop("ro.hardware"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "device=     %s", getprop("ro.product.device"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "brand=      %s", getprop("ro.product.brand"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "model=      %s", getprop("ro.product.model"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "name=       %s", getprop("ro.product.name"));
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "user=       %s", getprop("ro.build.user"));
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeHook_hook(JNIEnv *env, jclass obj, jstring packageName)
{
    __android_log_print(ANDROID_LOG_INFO, TAG, "into hook");
    
    hookProp();
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "sdk=        %s", getprop("ro.build.version.sdk"));
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeHook_unhook(JNIEnv *env, jclass obj, jstring packageName)
{
    __android_log_print(ANDROID_LOG_INFO, TAG, "into unhook");

    unHookProp();
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "sdk=        %s", getprop("ro.build.version.sdk"));
}
