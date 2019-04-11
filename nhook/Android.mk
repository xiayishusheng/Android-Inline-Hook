LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := hook
LOCAL_SRC_FILES := $(LOCAL_PATH)/../obj/local/armeabi-v7a/libhook.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := nhook.bin
LOCAL_SRC_FILES := nhook.c
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := libhook
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE    := nhook
LOCAL_SRC_FILES := nhook.c
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := libhook
include $(BUILD_SHARED_LIBRARY)
