#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <android/log.h>
#include <sys/system_properties.h>

#define TAG "nprop--->"

char *props[] = {"ro.build.version.sdk",
                 "ro.hardware",
                 "ro.product.device",
                 "ro.product.brand",
                 "ro.product.model",
                 "ro.product.name",
                 "ro.build.user"};
int length = sizeof(props) / sizeof(props[0]);

char *getprop(char *key)
{
    // static char val[PROP_VALUE_MAX];
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

int main()
{
    getprops1();
    return 0;
}

JNIEXPORT void JNICALL Java_com_example_frida_NativeProp_prop(JNIEnv *env, jclass obj, jstring packageName)
{
    getprops2();
}
