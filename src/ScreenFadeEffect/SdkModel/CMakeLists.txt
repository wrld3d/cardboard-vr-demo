set(headers ${headers} ../src/ScreenFadeEffect/SdkModel
)
set(currsources
  ../src/ScreenFadeEffect/SdkModel/CMakeLists.txt
  ../src/ScreenFadeEffect/SdkModel/IScreenFadeEffectController.h
  ../src/ScreenFadeEffect/SdkModel/ScreenFadeEffectController.cpp
  ../src/ScreenFadeEffect/SdkModel/ScreenFadeEffectController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ScreenFadeEffect\\SdkModel FILES ${currsources})
