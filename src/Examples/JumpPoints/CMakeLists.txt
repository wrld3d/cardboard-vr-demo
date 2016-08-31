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
  ../src/Examples/JumpPoints/InteriorCameraAnimationPositionProvider.cpp
  ../src/Examples/JumpPoints/InteriorCameraAnimationPositionProvider.h
  ../src/Examples/JumpPoints/FloorSwitchCameraAnimator.cpp
  ../src/Examples/JumpPoints/FloorSwitchCameraAnimator.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\JumpPoints FILES ${currsources})
