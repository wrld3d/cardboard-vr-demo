set(headers ${headers} ../src/Modules/SkyboxModule/
)
set(currsources
  ../src/Modules/UI/UIQuad.cpp
  ../src/Modules/UI/UIQuad.h
  ../src/Modules/UI/UIMeshRenderable.cpp
  ../src/Modules/UI/UIMeshRenderable.h
  ../src/Modules/UI/UIGeometryHelpers.cpp
  ../src/Modules/UI/UIGeometryHelpers.h
  ../src/Modules/UI/UIInteractionModule.cpp
  ../src/Modules/UI/UIInteractionModule.h
  ../src/Modules/UI/UIImageButton.cpp
  ../src/Modules/UI/UIImageButton.h
  ../src/Modules/UI/IUIInteractableItem.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\ FILES ${currsources})
