set(headers ${headers} ../src/Modules/UI/UIInteraction/
)
set(currsources
  ../src/Modules/UI/UIInteraction/IUIInteractableItem.h
  ../src/Modules/UI/UIInteraction/IUIInteractionObservable.h
  ../src/Modules/UI/UIInteraction/UIInteractionModule.cpp
  ../src/Modules/UI/UIInteraction/UIInteractionModule.h
)


set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\UIInteraction\\ FILES ${currsources})