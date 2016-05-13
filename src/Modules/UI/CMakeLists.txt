set(headers ${headers} ../src/Modules/SkyboxModule/
)
set(currsources
  ../src/Modules/UI/UIQuad.cpp
  ../src/Modules/UI/UIQuad.h
  ../src/Modules/UI/UIMeshRenderable.cpp
  ../src/Modules/UI/UIMeshRenderable.h
  ../src/Modules/UI/UIGeometryHelpers.cpp
  ../src/Modules/UI/UIGeometryHelpers.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\ FILES ${currsources})
