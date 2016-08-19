set(headers ${headers} ../src/Modules/SplashScreen/
)
set(currsources
  ../src/Modules/SplashScreen/StateButton.cpp
  ../src/Modules/SplashScreen/StateButton.h
  ../src/Modules/SplashScreen/SplashScreen.cpp
  ../src/Modules/SplashScreen/SplashScreen.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\SplashScreen\\ FILES ${currsources})