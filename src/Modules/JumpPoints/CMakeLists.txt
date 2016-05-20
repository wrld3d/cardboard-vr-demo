set(headers ${headers} ../src/Modules/JumpPoints/
)
set(currsources
  ../src/Modules/JumpPoints/IJumpPointViewFactory.h
  ../src/Modules/JumpPoints/IJumpPointObservable.h
  ../src/Modules/JumpPoints/IJumpPointObserver.h
  ../src/Modules/JumpPoints/JumpPoint.cpp
  ../src/Modules/JumpPoints/JumpPoint.h
  ../src/Modules/JumpPoints/JumpPoints.h
  ../src/Modules/JumpPoints/JumpPointView.cpp
  ../src/Modules/JumpPoints/JumpPointView.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\JumpPoints\\ FILES ${currsources})
