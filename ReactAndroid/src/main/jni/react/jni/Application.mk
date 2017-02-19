APP_BUILD_SCRIPT := Android.mk

APP_ABI := armeabi-v7a x86
APP_PLATFORM := android-9

NDK_MODULE_PATH :=/Users/yinhf/work/source/react-native/ReactAndroid/src/main/jni:/Users/yinhf/work/source/react-native/ReactAndroid/src/main/jni/first-party:/Users/yinhf/work/source/react-native/ReactAndroid/src/main/jni/third-party:/Users/yinhf/work/source/react-native/ReactCommon

APP_STL := gnustl_shared

# Make sure every shared lib includes a .note.gnu.build-id header
APP_LDFLAGS := -Wl,--build-id

NDK_TOOLCHAIN_VERSION := 4.8
