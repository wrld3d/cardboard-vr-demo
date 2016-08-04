set(headers ${headers} ../src/Examples/JumpPoints
)
set(currsources
  ../src/Examples/JumpPoints/JumpPointsSwitcher.cpp
  ../src/Examples/JumpPoints/JumpPointsSwitcher.h
  ../src/Examples/JumpPoints/JumpPointsExample.cpp
  ../src/Examples/JumpPoints/JumpPointsExample.h
  ../src/Examples/JumpPoints/JumpPointsExampleFactory.cpp
  ../src/Examples/JumpPoints/JumpPointsExampleFactory.h
  ../src/Examples/JumpPoints/JumpPointsCameraController.cpp
  ../src/Examples/JumpPoints/JumpPointsCameraController.h
  ../src/Examples/JumpPoints/WelcomeNoteViewer.cpp
  ../src/Examples/JumpPoints/WelcomeNoteViewer.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\JumpPoints FILES ${currsources})
