set(headers ${headers} ../src/Modules/InteriorsExplorerModule/InteriorMenu/
)
set(currsources
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/IInteriorMenuItemViewFactory.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/IInteriorMenuItemObservable.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/IInteriorMenuItemObserver.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItem.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItem.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenu.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItemView.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItemView.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuModule.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuModule.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuController.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuController.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItemRepository.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItemRepository.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItemViewFactory.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuItemViewFactory.h
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuUIButton.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorMenu/InteriorMenuUIButton.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\InteriorsExplorerModule\\InteriorMenu\\ FILES ${currsources})
