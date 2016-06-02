set(headers ${headers} ../src/Modules/UI/
)


set(currsources
  ../src/Modules/UI/UIBaseItem.cpp
  ../src/Modules/UI/UIBaseItem.h
  ../src/Modules/UI/UISprite.cpp
  ../src/Modules/UI/UISprite.h
  ../src/Modules/UI/UIImageButton.cpp
  ../src/Modules/UI/UIImageButton.h
  ../src/Modules/UI/IUICameraProvider.h
  ../src/Modules/UI/UIAnimatedSprite.h
  ../src/Modules/UI/UIAnimatedSprite.cpp
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\ FILES ${currsources})
include(../src/Modules/UI/UIGaze/CMakeLists.txt)
include(../src/Modules/UI/UIInteraction/CMakeLists.txt)
include(../src/Modules/UI/UIQuad/CMakeLists.txt)
