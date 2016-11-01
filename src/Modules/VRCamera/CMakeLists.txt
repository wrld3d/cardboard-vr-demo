set(headers ${headers} ../src/Modules/VRCamera/
)
set(currsources
  ../src/Modules/VRCamera/VRCamera.h
  ../src/Modules/VRCamera/VRRenderCamera.cpp
  ../src/Modules/VRCamera/VRRenderCamera.h
  ../src/Modules/VRCamera/VRCameraState.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\VRCamera\\ FILES ${currsources})
