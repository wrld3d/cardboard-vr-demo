set(headers ${headers} ../src/
)
set(currsources
  ../src/ExampleApp.cpp
  ../src/ExampleApp.h
  ../src/Logger.h
  ../src/ApiKey.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ FILES ${currsources})
include(../src/Examples/CMakeLists.txt)
include(../src/Modules/CMakeLists.txt)
include(../src/ApplicationConfig/CMakeLists.txt)
include(../src/WorldMenuLoader/CMakeLists.txt)