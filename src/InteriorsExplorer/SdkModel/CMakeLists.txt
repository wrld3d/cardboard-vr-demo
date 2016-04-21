set(headers ${headers} ../src/InteriorsExplorer/SdkModel
)
set(currsources
  ../src/InteriorsExplorer/SdkModel/CMakeLists.txt
  ../src/InteriorsExplorer/SdkModel/IInteriorsExplorerModule.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModel.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModel.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModule.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModule.h
  ../src/InteriorsExplorer/SdkModel/InteriorVisibilityUpdater.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorVisibilityUpdater.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsExplorer\\SdkModel FILES ${currsources})
