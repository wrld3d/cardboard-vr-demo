set(headers ${headers} ../src/WorldMenuLoader
)
set(currsources
  ../src/WorldMenuLoader/WorldMenuLoader.h
  ../src/WorldMenuLoader/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\WorldMenuLoader FILES ${currsources})
include(../src/WorldMenuLoader/SdkModel/CMakeLists.txt)
