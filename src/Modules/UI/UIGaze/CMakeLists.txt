set(headers ${headers} ../src/Modules/UI/UIGaze/
)
set(currsources
  ../src/Modules/UI/UIGaze/UIGazeView.h
  ../src/Modules/UI/UIGaze/UIGazeView.cpp
  ../src/Modules/UI/UIGaze/IUIGazeView.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\UIGaze\\ FILES ${currsources})