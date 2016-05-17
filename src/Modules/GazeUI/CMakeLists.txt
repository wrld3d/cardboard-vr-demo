set(headers ${headers} ../src/Modules/GazeUI/
)
set(currsources
  ../src/Modules/GazeUI/GazeUI.h
  ../src/Modules/GazeUI/IGazeUIView.h
  ../src/Modules/GazeUI/IGazeUIModule.h
  ../src/Modules/GazeUI/GazeUIModule.cpp
  ../src/Modules/GazeUI/GazeUIModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\GazeUI\\ FILES ${currsources})