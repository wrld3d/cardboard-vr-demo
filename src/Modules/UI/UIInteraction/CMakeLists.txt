set(headers ${headers} ../src/Modules/UI/UIInteraction/
)
set(currsources
  ../src/Modules/UI/UIInteraction/IUIInteractableItem.h
  ../src/Modules/UI/UIInteraction/IUIInteractionObservable.h
  ../src/Modules/UI/UIInteraction/UIInteractionController.cpp
  ../src/Modules/UI/UIInteraction/UIInteractionController.h
)


set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\UIInteraction\\ FILES ${currsources})