/*
 * Copyright 2016 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#if !defined(FOLLY_MOBILE)
#if defined(__ANDROID__) || \
    (defined(__APPLE__) &&  \
     (TARGET_IPHONE_SIMULATOR || TARGET_OS_SIMULATOR || TARGET_OS_IPHONE))
#define FOLLY_MOBILE 1
#else
#define FOLLY_MOBILE 0
#endif
#endif // FOLLY_MOBILE

/* #undef FOLLY_HAVE_PTHREAD */
//#define FOLLY_HAVE_PTHREAD_ATFORK 1

//#define FOLLY_HAVE_LIBGFLAGS 1
/* #undef FOLLY_UNUSUAL_GFLAGS_NAMESPACE */
//#define FOLLY_GFLAGS_NAMESPACE gflags

#define FOLLY_HAVE_LIBGLOG 1

/* #undef FOLLY_HAVE_MALLOC_H */
/* #undef FOLLY_HAVE_BITS_FUNCTEXCEPT_H */
/* #undef FOLLY_HAVE_BITS_CXXCONFIG_H */
/* #undef FOLLY_HAVE_FEATURES_H */
/* #undef FOLLY_HAVE_LINUX_MEMBARRIER_H */
/* #undef FOLLY_USE_JEMALLOC */

//#if FOLLY_HAVE_FEATURES_H
//#include <features.h>
//#endif

#define FOLLY_HAVE_MEMRCHR 1
/* #undef FOLLY_HAVE_PREADV */
/* #undef FOLLY_HAVE_PWRITEV */
/* #undef FOLLY_HAVE_CLOCK_GETTIME */
/* #undef FOLLY_HAVE_CPLUS_DEMANGLE_V3_CALLBACK */
#define FOLLY_HAVE_OPENSSL_ASN1_TIME_DIFF 1

/* #undef FOLLY_HAVE_IFUNC */
#define FOLLY_HAVE_STD__IS_TRIVIALLY_COPYABLE 1
#define FOLLY_HAVE_UNALIGNED_ACCESS 1
#define FOLLY_HAVE_VLA 1
/* #undef FOLLY_HAVE_WEAK_SYMBOLS */
/* #undef FOLLY_HAVE_LINUX_VDSO */
/* #undef FOLLY_HAVE_MALLOC_USABLE_SIZE */
/* #undef FOLLY_HAVE_INT128_T */
/* #undef FOLLY_SUPPLY_MISSING_INT128_TRAITS */
#define FOLLY_HAVE_WCHAR_SUPPORT 1
/* #undef FOLLY_HAVE_EXTRANDOM_SFMT19937 */
#define FOLLY_USE_LIBCPP 1
#define FOLLY_HAVE_XSI_STRERROR_R 1
/* #undef HAVE_VSNPRINTF_ERRORS */

#define FOLLY_VERSION "0.58.0-dev"

/* #undef FOLLY_HAVE_LIBDWARF_DWARF_H */
/* #undef FOLLY_USE_SYMBOLIZER */
#define FOLLY_DEMANGLE_MAX_SYMBOL_SIZE 1024

/* #undef FOLLY_HAVE_SHADOW_LOCAL_WARNINGS */

//#define FOLLY_HAVE_LIBLZ4 1
//#define FOLLY_HAVE_LIBLZMA 1
//#define FOLLY_HAVE_LIBSNAPPY 1
//#define FOLLY_HAVE_LIBZ 1
/* #undef FOLLY_HAVE_LIBZSTD */
//#define FOLLY_HAVE_LIBBZ2 1

#define FOLLY_SUPPORT_SHARED_LIBRARY 1
