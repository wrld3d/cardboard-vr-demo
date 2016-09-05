set(headers ${headers} ../src/Modules/InteriorsExplorerModule/
)
set(currsources
  ../src/Modules/InteriorsExplorerModule/IInteriorsExplorerModule.h
  ../src/Modules/InteriorsExplorerModule/InteriorsExplorerModel.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorsExplorerModel.h
  ../src/Modules/InteriorsExplorerModule/InteriorsExplorerModule.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorsExplorerModule.h
  ../src/Modules/InteriorsExplorerModule/InteriorVisibilityUpdater.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorVisibilityUpdater.h
  ../src/Modules/InteriorsExplorerModule/InteriorDistanceVisibilityUpdater.cpp
  ../src/Modules/InteriorsExplorerModule/InteriorDistanceVisibilityUpdater.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\InteriorsExplorerModule\\ FILES ${currsources})
include(../src/Modules/InteriorsExplorerModule/InteriorMenu/CMakeLists.txt)