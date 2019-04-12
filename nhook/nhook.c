#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <android/log.h>
#include <sys/system_properties.h>

#include "inlineHook.h"

#define TAG "nhook--->"

char *props[] = {"ro.build.version.sdk",
                 "ro.hardware",
                 "ro.product.device",
                 "ro.product.brand",
                 "ro.product.model",
                 "ro.product.name",
                 "ro.build.user"};
int length = sizeof(props) / sizeof(props[0]);

int (*old_prop)(const char *) = NULL;
bool is_hook = false;

char *getprop(char *key)
{
    char *val = malloc(PROP_VALUE_MAX);
    memset(val, 0, sizeof(char) * PROP_VALUE_MAX);
    __system_property_get(key, val);
    return val;
}

void getprops1()
{
    for (int i = 0; i < length; i++)
    {
        printf("%s=%s\n", props[i], getprop(props[i]));
    }
}

void getprops2()
{
    for (int i = 0; i < length; i++)
    {
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "%s=%s", props[i], getprop(props[i]));
    }
}

int new_prop(const char *key, char *value)
{
    char *newvalue;
    if (strcmp(key, "ro.build.version.sdk") == 0)
    {
        newvalue = "26";
        memcpy(value, newvalue, strlen(newvalue));
    }
    else if (strcmp(key, "ro.hardware") == 0)
    {
        newvalue = "myhardware";
        memcpy(value, newvalue, strlen(newvalue));
    }
    else if (strcmp(key, "ro.product.device") == 0)
    {
        newvalue = "mydevice";
        memcpy(value, newvalue, strlen(newvalue));
    }
    else if (strcmp(key, "ro.product.brand") == 0)
    {
        newvalue = "mybrand";
        memcpy(value, newvalue, strlen(newvalue));
    }
    else if (strcmp(key, "ro.product.model") == 0)
    {
        newvalue = "mymodel";
        memcpy(value, newvalue, strlen(newvalue));
    }
    else if (strcmp(key, "ro.product.name") == 0)
    {
        newvalue = "myname";
        memcpy(value, newvalue, strlen(newvalue));
    }
    else if (strcmp(key, "ro.build.user") == 0)
    {
        newvalue = "myuser";
        memcpy(value, newvalue, strlen(newvalue));
    }
    else
    {
        newvalue = "others";
        memcpy(value, newvalue, strlen(newvalue));
    }
    return 0;
}

int hookProp()
{
    if (!is_hook)
    {
        if (registerInlineHook((uint32_t)__system_property_get, (uint32_t)new_prop, (uint32_t **)&old_prop) != ELE7EN_OK)
        {
            return -1;
        }
        if (inlineHook((uint32_t)__system_property_get) != ELE7EN_OK)
        {
            return -1;
        }
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "hook success!");
        is_hook = true;
        return 0;
    }
    else
    {
        __android_log_print(ANDROID_LOG_WARN, TAG, "has been hooked!");
        return -2;
    }
}

int unHookProp()
{
    if (is_hook)
    {
        if (inlineUnHook((uint32_t)__system_property_get) != ELE7EN_OK)
        {
            return -1;
        }
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "unhook!");
        is_hook = false;
        return 0;
    }
    else
    {
        __android_log_print(ANDROID_LOG_WARN, TAG, "is not hook!");
        return -2;
    }
}

int main()
{
    printf("==========props==========\n");
    getprops1();

    printf("==========hook==========\n");
    hookProp();
    getprops1();

    printf("==========unhook==========\n");
    unHookProp();
    getprops1();

    return 0;
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeHook_prop(JNIEnv *env, jclass obj, jstring packageName)
{
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "==========props==========");
    getprops2();
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeHook_hook(JNIEnv *env, jclass obj, jstring packageName)
{
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "==========hook==========");
    hookProp();
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeHook_unhook(JNIEnv *env, jclass obj, jstring packageName)
{
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "==========unhook==========");
    unHookProp();
}
