set(headers ${headers} ../src/Examples/VRCameraSpline
)
set(currsources
  ../src/Examples/VRCameraSpline/VRCameraPositionSpline.h  ../src/Examples/VRCameraSpline/VRCameraSplineExample.cpp  ../src/Examples/VRCameraSpline/VRCameraSplineExample.h  ../src/Examples/VRCameraSpline/VRCameraSplineExampleFactory.cpp  ../src/Examples/VRCameraSpline/VRCameraSplineExampleFactory.h  ../src/Examples/VRCameraSpline/VREegeoCameraController.cpp  ../src/Examples/VRCameraSpline/VREegeoCameraController.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\VRCameraSpline FILES ${currsources})