set(headers ${headers} ../src/Modules/DeadZoneMenu/
)
set(currsources
  ../src/Modules/DeadZoneMenu/IDeadZoneMenuItemViewFactory.h
  ../src/Modules/DeadZoneMenu/IDeadZoneMenuItemObservable.h
  ../src/Modules/DeadZoneMenu/IDeadZoneMenuItemObserver.h
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItem.cpp
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItem.h
  ../src/Modules/DeadZoneMenu/DeadZoneMenu.h
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItemView.cpp
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItemView.h
  ../src/Modules/DeadZoneMenu/DeadZoneMenuModule.cpp
  ../src/Modules/DeadZoneMenu/DeadZoneMenuModule.h
  ../src/Modules/DeadZoneMenu/DeadZoneMenuController.cpp
  ../src/Modules/DeadZoneMenu/DeadZoneMenuController.h
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItemRepository.cpp
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItemRepository.h
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItemViewFactory.cpp
  ../src/Modules/DeadZoneMenu/DeadZoneMenuItemViewFactory.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\DeadZoneMenu\\ FILES ${currsources})
