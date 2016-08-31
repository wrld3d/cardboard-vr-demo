set(headers ${headers} ../src/Modules/WorldMenu/
)
set(currsources
  ../src/Modules/WorldMenu/IWorldMenuItemViewFactory.h
  ../src/Modules/WorldMenu/IWorldMenuItemObservable.h
  ../src/Modules/WorldMenu/IWorldMenuItemObserver.h
  ../src/Modules/WorldMenu/WorldMenuItem.cpp
  ../src/Modules/WorldMenu/WorldMenuItem.h
  ../src/Modules/WorldMenu/WorldMenu.h
  ../src/Modules/WorldMenu/WorldMenuItemView.cpp
  ../src/Modules/WorldMenu/WorldMenuItemView.h
  ../src/Modules/WorldMenu/WorldMenuModule.cpp
  ../src/Modules/WorldMenu/WorldMenuModule.h
  ../src/Modules/WorldMenu/WorldMenuController.cpp
  ../src/Modules/WorldMenu/WorldMenuController.h
  ../src/Modules/WorldMenu/WorldMenuItemRepository.cpp
  ../src/Modules/WorldMenu/WorldMenuItemRepository.h
  ../src/Modules/WorldMenu/WorldMenuItemViewFactory.cpp
  ../src/Modules/WorldMenu/WorldMenuItemViewFactory.h
  ../src/Modules/WorldMenu/WorldMenuUIButton.cpp
  ../src/Modules/WorldMenu/WorldMenuUIButton.h
  ../src/Modules/WorldMenu/WorldMenuUpView.cpp
  ../src/Modules/WorldMenu/WorldMenuUpView.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\WorldMenu\\ FILES ${currsources})