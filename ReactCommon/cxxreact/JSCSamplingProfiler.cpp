// Copyright 2004-present Facebook. All Rights Reserved.

#include "JSCSamplingProfiler.h"

#include <jschelpers/JSCHelpers.h>

static JSValueRef pokeSamplingProfiler(
    JSContextRef ctx,
    JSObjectRef function,
    JSObjectRef thisObject,
    size_t argumentCount,
    const JSValueRef arguments[],
    JSValueRef* exception) {
  // XXXX
//  return JSC_JSPokeSamplingProfiler(ctx);
  return 0;
}

namespace facebook {
namespace react {

void initSamplingProfilerOnMainJSCThread(JSGlobalContextRef ctx) {
  // XXXX
//  JSC_JSStartSamplingProfilingOnMainJSCThread(ctx);

  // Allow the profiler to be poked from JS as well
  // (see SamplingProfiler.js for an example of how it could be used with the JSCSamplingProfiler module).
  installGlobalFunction(ctx, "pokeSamplingProfiler", pokeSamplingProfiler);
}

} }
