set(headers ${headers} ../src/VRDistortion
)
set(currsources  ../src/VRDistortion/VRDistortionMaterial.cpp  ../src/VRDistortion/VRDistortionMaterial.h  ../src/VRDistortion/VRDistortionRenderable.cpp  ../src/VRDistortion/VRDistortionRenderable.h  ../src/VRDistortion/VRDistortionRenderer.cpp  ../src/VRDistortion/VRDistortionRenderer.h  ../src/VRDistortion/VRDistortionShader.cpp  ../src/VRDistortion/VRDistortionShader.h  ../src/VRDistortion/VRDistortion.cpp  ../src/VRDistortion/VRDistortion.h
  ../src/VRDistortion/VRDistortionIncludes.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\VRDistortion FILES ${currsources})
