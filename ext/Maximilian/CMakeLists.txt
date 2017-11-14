cmake_minimum_required(VERSION 3.2.0)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMAKE_BUILD_TYPE: Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(TARGET "maximilian")

SET(EXTARGET "maximilian-exec")

SET(SRC
  RtAudio.cpp
  player.cpp
  maximilian.cpp

  maximilian.h
  player.h
  portaudio.h
  RtAudio.h
  RtError)


add_subdirectory(ext/portaudio)
INCLUDE_DIRECTORIES(ext/portaudio/include)

ADD_DEFINITIONS(-Wall -D__LINUX_ALSA__)

ADD_LIBRARY(${TARGET} ${SRC})
TARGET_LINK_LIBRARIES(${TARGET} "-lsndfile -lpthread -lasound" portaudio)

ADD_EXECUTABLE(${EXTARGET} "main.cpp" ${SRC})
TARGET_LINK_LIBRARIES(${EXTARGET} "-lsndfile -lpthread -lasound" portaudio)
