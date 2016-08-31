set(headers ${headers} ../src/Modules/UI/UIQuad/
)
set(currsources
  ../src/Modules/UI/UIQuad/UIGeometryHelpers.cpp
  ../src/Modules/UI/UIQuad/UIGeometryHelpers.h
  ../src/Modules/UI/UIQuad/UIQuad.cpp
  ../src/Modules/UI/UIQuad/UIQuad.h
  ../src/Modules/UI/UIQuad/UITexturedUniformColoredMaterial.cpp
  ../src/Modules/UI/UIQuad/UITexturedUniformColoredMaterial.h
  ../src/Modules/UI/UIQuad/UIMeshRenderable.cpp
  ../src/Modules/UI/UIQuad/UIMeshRenderable.h
  ../src/Modules/UI/UIQuad/UIQuadFactory.cpp
  ../src/Modules/UI/UIQuad/UIQuadFactory.h
  ../src/Modules/UI/UIQuad/IUIQuadFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\UIQuad\\ FILES ${currsources})

