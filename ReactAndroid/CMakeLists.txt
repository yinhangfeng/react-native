# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

# XXX -std=gnu++11 -std=c++11

cmake_minimum_required(VERSION 3.4.1)

set(jni_dir ${CMAKE_SOURCE_DIR}/src/main/jni)

#
# third-party-ndk
#

set(third_party_ndk_dir ${CMAKE_SOURCE_DIR}/third-party-ndk)

# boost(header-only) https://cmake.org/cmake/help/v3.6/manual/cmake-buildsystem.7.html#interface-libraries
set(boost_dir ${third_party_ndk_dir}/boost)
add_library(boost
            INTERFACE)
target_include_directories(boost
                           INTERFACE
                           ${boost_dir}/boost_1_63_0)

# glog libglog.so
set(glog_dir third-party-ndk/glog)
add_library(glog
            SHARED
            ${glog_dir}/glog-0.3.3/src/demangle.cc
            ${glog_dir}/glog-0.3.3/src/logging.cc
            ${glog_dir}/glog-0.3.3/src/raw_logging.cc
            ${glog_dir}/glog-0.3.3/src/signalhandler.cc
            ${glog_dir}/glog-0.3.3/src/symbolize.cc
            ${glog_dir}/glog-0.3.3/src/utilities.cc
            ${glog_dir}/glog-0.3.3/src/vlog_is_on.cc)
target_include_directories(glog
                           PRIVATE
                           ${glog_dir}
                           PUBLIC
                           ${glog_dir}/..
                           ${glog_dir}/glog-0.3.3/src)
target_compile_options(glog
                       PRIVATE
                       -Wall
                       -Wwrite-strings
                       -Woverloaded-virtual
                       -Wno-sign-compare
                       -g
                       -O2)
# XXX _START_GOOGLE_NAMESPACE_ _END_GOOGLE_NAMESPACE_ 已在 config.h 中定义
target_compile_definitions(glog
                           PRIVATE
                           NDEBUG)

# double-conversion
set(double-conversion_dir ${third_party_ndk_dir}/double-conversion)
add_library(double-conversion
            STATIC
            ${double-conversion_dir}/double-conversion/bignum.cc
            ${double-conversion_dir}/double-conversion/bignum-dtoa.cc
            ${double-conversion_dir}/double-conversion/cached-powers.cc
            ${double-conversion_dir}/double-conversion/diy-fp.cc
            ${double-conversion_dir}/double-conversion/double-conversion.cc
            ${double-conversion_dir}/double-conversion/fast-dtoa.cc
            ${double-conversion_dir}/double-conversion/fixed-dtoa.cc
            ${double-conversion_dir}/double-conversion/strtod.cc)
target_include_directories(double-conversion
                           PUBLIC ${double-conversion_dir})
target_compile_options(double-conversion
                       PUBLIC
                       -std=c++11 -Wno-unused-variable -Wno-unused-local-typedefs)

# folly_json libfolly_json.so
set(folly_json_dir ${third_party_ndk_dir}/folly)
add_library(folly_json
            SHARED
            ${folly_json_dir}/folly/json.cpp
            ${folly_json_dir}/folly/Unicode.cpp
            ${folly_json_dir}/folly/Conv.cpp
            ${folly_json_dir}/folly/Demangle.cpp
            ${folly_json_dir}/folly/detail/MallocImpl.cpp
            ${folly_json_dir}/folly/StringBase.cpp
            ${folly_json_dir}/folly/dynamic.cpp)
target_include_directories(folly_json
                           PUBLIC ${folly_json_dir})
target_compile_options(folly_json
                       PRIVATE
                       -fexceptions -fno-omit-frame-pointer -frtti -Wall -Werror -std=c++11
                       PUBLIC
                       -std=gnu++11)
target_compile_definitions(folly_json
                           PUBLIC
                           FOLLY_NO_CONFIG=1
                           FOLLY_HAVE_CLOCK_GETTIME=1)
target_link_libraries(folly_json
                      glog
                      double-conversion
                      boost)

# jsc libjsc.so
set(jsc_dir ${third_party_ndk_dir}/jsc)
add_library(jsc
            SHARED
            IMPORTED)
set_target_properties(jsc
                      PROPERTIES IMPORTED_LOCATION
                      ${jsc_dir}/jni/${ANDROID_ABI}/libjsc.so)
# target_include_directories(jsc PUBLIC ${jsc_dir})


#
# jni common
#

# fb libfb.so
set(fb_dir ${jni_dir}/first-party/fb)
add_library(fb
            SHARED
            ${fb_dir}/assert.cpp
            ${fb_dir}/jni/ByteBuffer.cpp
            ${fb_dir}/jni/Countable.cpp
            ${fb_dir}/jni/Environment.cpp
            ${fb_dir}/jni/Exceptions.cpp
            ${fb_dir}/jni/fbjni.cpp
            ${fb_dir}/jni/Hybrid.cpp
            ${fb_dir}/jni/jni_helpers.cpp
            ${fb_dir}/jni/LocalString.cpp
            ${fb_dir}/jni/OnLoad.cpp
            ${fb_dir}/jni/References.cpp
            ${fb_dir}/jni/WeakReference.cpp
            ${fb_dir}/log.cpp
            ${fb_dir}/lyra/lyra.cpp
            ${fb_dir}/onload.cpp)
target_include_directories(fb
                           PUBLIC ${fb_dir}/include)
# TODO TOOLCHAIN_PERMISSIVE
target_compile_options(fb
                       PRIVATE
                       -fexceptions -frtti -Wall -Werror -Wno-unused-parameter
                       PUBLIC
                       -std=gnu++11)
target_compile_definitions(fb
                           PRIVATE
                           LOG_TAG=\"libfb\"
                           DISABLE_CPUCAP
                           DISABLE_XPLAT
                           HAVE_POSIX_CLOCKS)
target_link_libraries(fb
                      PRIVATE
                      dl
                      android
                      PUBLIC
                      log)


#
# ReactCommon
#

set(react_common_dir ${CMAKE_SOURCE_DIR}/../ReactCommon)

# jschelpers
set(jschelpers_dir ${react_common_dir}/jschelpers)
add_library(jschelpers
            STATIC
            ${jschelpers_dir}/JSCHelpers.cpp
            ${jschelpers_dir}/Unicode.cpp
            ${jschelpers_dir}/Value.cpp)
target_include_directories(jschelpers
                           PRIVATE
                           ${jsc_dir}
                           PUBLIC
                           ${jschelpers_dir}/..)
target_compile_options(jschelpers
                       PRIVATE
                       -Wall -Werror -fexceptions -frtti
                       PUBLIC
                       -std=c++11)
target_compile_definitions(jschelpers
                           PRIVATE
                           LOG_TAG=\"ReactNative\")
target_link_libraries(jschelpers
                      folly_json
                      jsc
                      glog)

# cxxreact(reactnative)
set(cxxreact_dir ${react_common_dir}/cxxreact)
add_library(reactnative
            STATIC
            ${cxxreact_dir}/CxxNativeModule.cpp
            ${cxxreact_dir}/Instance.cpp
            ${cxxreact_dir}/JSBigString.cpp
            ${cxxreact_dir}/JSBundleType.cpp
            ${cxxreact_dir}/JSCExecutor.cpp
            ${cxxreact_dir}/JSCLegacyTracing.cpp
            ${cxxreact_dir}/JSCMemory.cpp
            ${cxxreact_dir}/JSCNativeModules.cpp
            ${cxxreact_dir}/JSCPerfStats.cpp
            ${cxxreact_dir}/JSCSamplingProfiler.cpp
            ${cxxreact_dir}/JSCTracing.cpp
            ${cxxreact_dir}/JSCUtils.cpp
            ${cxxreact_dir}/JSIndexedRAMBundle.cpp
            ${cxxreact_dir}/MethodCall.cpp
            ${cxxreact_dir}/ModuleRegistry.cpp
            ${cxxreact_dir}/NativeToJsBridge.cpp
            ${cxxreact_dir}/Platform.cpp
            ${cxxreact_dir}/RAMBundleRegistry.cpp)
target_include_directories(reactnative
                           PRIVATE
                           ${jsc_dir}
                           PUBLIC
                           ${cxxreact_dir}/..)
target_compile_options(reactnative
                       PRIVATE
                       -Wall -Werror -fexceptions -frtti
                       PUBLIC
                       -std=c++11)
target_compile_definitions(reactnative
                           PRIVATE
                           LOG_TAG=\"ReactNative\")
target_link_libraries(reactnative
                      jschelpers
                      fb
                      folly_json
                      jsc
                      glog)

# yogacore
set(yogacore_dir ${react_common_dir}/yoga)
file(GLOB_RECURSE yogacore_srcs ${yogacore_dir}/yoga/*.cpp)
add_library(yogacore
            STATIC
            ${yogacore_srcs})
target_include_directories(yogacore
                           PUBLIC ${yogacore_dir})
target_compile_options(yogacore
                       PRIVATE
                       -Wall -Werror -fexceptions -frtti -std=c++1y -O3)

# privatedata libprivatedata.so
set(privatedata_dir ${react_common_dir}/privatedata)
add_library(privatedata
            SHARED
            ${privatedata_dir}/PrivateDataBase.cpp)
target_include_directories(privatedata
                           PUBLIC ${privatedata_dir}/..)
target_compile_options(privatedata
                       PRIVATE
                       -Wall -Werror -fexceptions -frtti
                       PUBLIC
                       -std=c++11)
target_compile_definitions(privatedata
                           PRIVATE
                           LOG_TAG=\"ReactNative\")

# jsinspector .so?
set(jsinspector_dir ${react_common_dir}/jsinspector)
add_library(jsinspector
            SHARED
            ${jsinspector_dir}/InspectorInterfaces.cpp)
target_include_directories(jsinspector
                           PUBLIC ${jsinspector_dir}/..)
target_compile_options(jsinspector
                       PRIVATE
                       -Wall -Werror -fexceptions -frtti
                       PUBLIC
                       -std=c++11)


#
# jni
#

# yoga(libyoga.so)
set(yoga_dir ${jni_dir}/first-party/yogajni)
add_library(yoga
            SHARED
            ${yoga_dir}/jni/YGJNI.cpp)
target_include_directories(yoga
                           PRIVATE ${yoga_dir}/jni)
target_compile_options(yoga
                       PRIVATE
                       -Wall -Werror -fvisibility=hidden -fexceptions -frtti -O3
                       PUBLIC
                       -std=c++11)
target_link_libraries(yoga
                      yogacore
                      fb)

# gloginit libgloginit.so
set(gloginit_dir ${jni_dir}/first-party/fbgloginit)
add_library(gloginit
            SHARED
            ${gloginit_dir}/glog_init.cpp)
target_include_directories(gloginit
                           PUBLIC ${gloginit_dir})
target_compile_options(gloginit
                       PRIVATE
                       -fexceptions -fno-omit-frame-pointer -Wall -Werror
                       PUBLIC
                       -std=gnu++11)
target_link_libraries(gloginit
                      log
                      glog)

# packagerconnectionjnifb ?
# set(packagerconnectionjnifb_dir ${jni_dir}/packagerconnection)
# add_library(packagerconnectionjnifb
#             SHARED
#            ${packagerconnectionjnifb_dir}/JSPackagerClientResponder.h
#            ${packagerconnectionjnifb_dir}/SamplingProfilerPackagerMethod.cpp)
# target_include_directories(packagerconnectionjnifb
#                            PRIVATE ${packagerconnectionjnifb_dir}/../..)
# target_link_libraries(packagerconnectionjnifb
#                       folly_json
#                       fbjni
#                       jsc
#                       glog_init)

# libreactnativejni.so
set(reactnativejni_dir ${jni_dir}/react/jni)
add_library(reactnativejni
            SHARED
            ${reactnativejni_dir}/AndroidJSCFactory.cpp
            ${reactnativejni_dir}/CatalystInstanceImpl.cpp
            ${reactnativejni_dir}/CxxModuleWrapper.cpp
            ${reactnativejni_dir}/JavaModuleWrapper.cpp
            ${reactnativejni_dir}/JMessageQueueThread.cpp
            ${reactnativejni_dir}/JSCPerfLogging.cpp
            ${reactnativejni_dir}/JSLoader.cpp
            ${reactnativejni_dir}/JSLogging.cpp
            ${reactnativejni_dir}/JniJSModulesUnbundle.cpp
            ${reactnativejni_dir}/MethodInvoker.cpp
            ${reactnativejni_dir}/ModuleRegistryBuilder.cpp
            ${reactnativejni_dir}/NativeArray.cpp
            ${reactnativejni_dir}/NativeCommon.cpp
            ${reactnativejni_dir}/NativeMap.cpp
            ${reactnativejni_dir}/OnLoad.cpp
            ${reactnativejni_dir}/ProxyExecutor.cpp
            ${reactnativejni_dir}/ReactMarker.cpp
            ${reactnativejni_dir}/ReadableNativeArray.cpp
            ${reactnativejni_dir}/ReadableNativeMap.cpp
            ${reactnativejni_dir}/WritableNativeArray.cpp
            ${reactnativejni_dir}/WritableNativeMap.cpp)
target_include_directories(reactnativejni
                           PRIVATE
                           ${jsc_dir}
                           PUBLIC
                           ${reactnativejni_dir}/../..)
target_compile_options(reactnativejni
                       PRIVATE
                       -Wall -Werror -fvisibility=hidden -fexceptions -frtti
                       PUBLIC
                       -std=c++11)
# TODO fbjni?
target_link_libraries(reactnativejni
                      PRIVATE
                      reactnative
                      folly_json
                      fb
                      jsc
                      glog_init
                      yoga
                      privatedata)

function(configure_shared_stl lib_path so_base)
  message("Configuring STL ${so_base} for ${ANDROID_ABI}")
  configure_file(
    "${ANDROID_NDK}/sources/cxx-stl/${lib_path}/libs/${ANDROID_ABI}/lib${so_base}.so"
    "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${so_base}.so"
    COPYONLY)
endfunction()
configure_shared_stl("llvm-libc++" "c++_shared")
