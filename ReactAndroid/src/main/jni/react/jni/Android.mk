LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libreactnativejni

LOCAL_SRC_FILES := \
  Dummy.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../.. $(LOCAL_PATH)/..

LOCAL_CFLAGS += -Wall -Werror -fvisibility=hidden -fexceptions -frtti
CXX11_FLAGS := -std=c++11
LOCAL_CFLAGS += $(CXX11_FLAGS)
LOCAL_EXPORT_CPPFLAGS := $(CXX11_FLAGS)

LOCAL_LDLIBS += -landroid
LOCAL_SHARED_LIBRARIES := libreactnativejnifb
LOCAL_STATIC_LIBRARIES :=

include $(BUILD_SHARED_LIBRARY)

#$(call import-add-path,/Users/yinhf/work/source/react-native/ReactAndroid/src/main/jni)
#$(call import-add-path,/Users/yinhf/work/source/react-native/ReactAndroid/src/main/jni/first-party)
#$(call import-add-path,/Users/yinhf/work/source/react-native/ReactAndroid/src/main/jni/third-party)
#$(call import-add-path,/Users/yinhf/work/source/react-native/ReactCommon)
$(call import-module,xreact/jni)
