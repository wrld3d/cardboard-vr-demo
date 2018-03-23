# Absorb Android.mk

if(${ANDROID})
set(headers ${headers} jni
)
set(currsources
  jni/AndroidVRHeadTracker.h
  jni/AndroidVRHeadTracker.cpp
  jni/AppHost.h
  jni/AppHost.cpp
  jni/AppInputDelegate.h
  jni/AppInputDelegate.cpp
  jni/AppRunner.h
  jni/AppRunner.cpp
  jni/GlDisplayService.h
  jni/GlDisplayService.cpp
  jni/main.cpp
  jni/main.h
)
set(sources ${sources} ${currsources})
source_group(\\jni FILES ${currsources})
include(jni/ApplicationConfig/CMakeLists.txt)
include(jni/Examples/CMakeLists.txt)
endif(${ANDROID})
