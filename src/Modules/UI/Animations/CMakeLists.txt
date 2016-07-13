set(headers ${headers} ../src/Modules/UI/Animations/
)
set(currsources
../src/Modules/UI/Animations/AnimationsController.cpp
../src/Modules/UI/Animations/AnimationsController.h
../src/Modules/UI/Animations/AnimationsFactory.cpp
../src/Modules/UI/Animations/AnimationsFactory.h
../src/Modules/UI/Animations/IAnimation.h
../src/Modules/UI/Animations/IAnimationObservable.h
../src/Modules/UI/Animations/IAnimationObserver.h
../src/Modules/UI/Animations/IAnimationsFactory.h
../src/Modules/UI/Animations/IEase.h
../src/Modules/UI/Animations/IDv3Animateable.h
../src/Modules/UI/Animations/Dv3PropertyAnimation.cpp
../src/Modules/UI/Animations/Dv3PropertyAnimation.h
../src/Modules/UI/Animations/AnimationEase.cpp
../src/Modules/UI/Animations/AnimationEase.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\UI\\Animations\\ FILES ${currsources})
