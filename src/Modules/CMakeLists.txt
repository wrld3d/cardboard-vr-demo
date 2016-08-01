set(headers ${headers} ../src/Modules/
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\ FILES ${currsources})
include(../src/Modules/InteriorsExplorerModule/CMakeLists.txt)
include(../src/Modules/VRDistortionModule/CMakeLists.txt)
include(../src/Modules/SkyboxModule/CMakeLists.txt)
include(../src/Modules/UI/CMakeLists.txt)
include(../src/Modules/JumpPoints/CMakeLists.txt)
include(../src/Modules/DeadZoneMenu/CMakeLists.txt)
include(../src/Modules/WorldMenu/CMakeLists.txt)
