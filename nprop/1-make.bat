ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk APP_PLATFORM=android-21 & adb push libs /data/local/tmp & adb shell "chmod 777 -R /data/local/tmp"
