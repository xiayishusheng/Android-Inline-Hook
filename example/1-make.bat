ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk & adb push libs/armeabi-v7a/hooktest /data/local/tmp & adb shell "chmod 777 /data/local/tmp/hooktest"
