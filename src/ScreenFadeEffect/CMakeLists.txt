set(headers ${headers} ../src/ScreenFadeEffect
)
set(currsources
  ../src/ScreenFadeEffect/ScreenFadeEffect.h
  ../src/ScreenFadeEffect/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\ScreenFadeEffect FILES ${currsources})
include(../src/ScreenFadeEffect/SdkModel/CMakeLists.txt)
