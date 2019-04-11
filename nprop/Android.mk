LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := nprop.bin
LOCAL_SRC_FILES := nprop.c
LOCAL_LDLIBS := -llog
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE    := nprop
LOCAL_SRC_FILES := nprop.c
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)
