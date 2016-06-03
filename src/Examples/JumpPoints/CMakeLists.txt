set(headers ${headers} ../src/Examples/JumpPoints
)
set(currsources
  ../src/Examples/JumpPoints/JumpPointsExample.cpp
  ../src/Examples/JumpPoints/JumpPointsExample.h
  ../src/Examples/JumpPoints/JumpPointsExampleFactory.cpp
  ../src/Examples/JumpPoints/JumpPointsExampleFactory.h
  ../src/Examples/JumpPoints/JumpPointsCameraController.cpp
  ../src/Examples/JumpPoints/JumpPointsCameraController.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\JumpPoints FILES ${currsources})
