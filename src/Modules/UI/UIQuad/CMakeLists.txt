set(headers ${headers} ../src/Modules/UI/UIQuad/
)
set(currsources
  ../src/Modules/UI/UIQuad/UIGeometryHelpers.cpp
  ../src/Modules/UI/UIQuad/UIGeometryHelpers.h
  ../src/Modules/UI/UIQuad/UIQuad.cpp
  ../src/Modules/UI/UIQuad/UIQuad.h
  ../src/Modules/UI/UIQuad/UIMeshRenderable.cpp
  ../src/Modules/UI/UIQuad/UIMeshRenderable.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\UIQuad\\ FILES ${currsources})
