set(headers ${headers} ../src/WorldMenuLoader/SdkModel
)
set(currsources
  ../src/WorldMenuLoader/SdkModel/CMakeLists.txt
  ../src/WorldMenuLoader/SdkModel/WorldMenuScreenFader.cpp
  ../src/WorldMenuLoader/SdkModel/WorldMenuScreenFader.h
  ../src/WorldMenuLoader/SdkModel/WorldMenuLoaderModel.cpp
  ../src/WorldMenuLoader/SdkModel/WorldMenuLoaderModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\WorldMenuLoader\\SdkModel FILES ${currsources})
