set(headers ${headers} ../src/Modules/UI/
)


set(currsources
  ../src/Modules/UI/UISprite.cpp
  ../src/Modules/UI/UISprite.h
  ../src/Modules/UI/UIImageButton.cpp
  ../src/Modules/UI/UIImageButton.h
  ../src/Modules/UI/UIProgressButton.cpp
  ../src/Modules/UI/UIProgressButton.h
  ../src/Modules/UI/IUICameraProvider.h
  ../src/Modules/UI/UIAnimatedSprite.h
  ../src/Modules/UI/UIAnimatedSprite.cpp
  ../src/Modules/UI/IUIRenderable.h
  ../src/Modules/UI/IUIRenderableFilter.h
  ../src/Modules/UI/UIRenderableFilter.cpp
  ../src/Modules/UI/UIRenderableFilter.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\ FILES ${currsources})
include(../src/Modules/UI/UIGaze/CMakeLists.txt)
include(../src/Modules/UI/UIInteraction/CMakeLists.txt)
include(../src/Modules/UI/UIQuad/CMakeLists.txt)
