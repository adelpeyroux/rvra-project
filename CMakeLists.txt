cmake_minimum_required(VERSION 3.2.0)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMAKE_BUILD_TYPE: Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)


FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_subdirectory(ext/aruco)
INCLUDE_DIRECTORIES(ext/aruco/src)

add_subdirectory(ext/Maximilian)
INCLUDE_DIRECTORIES(ext/Maximilian)


SET(TARGET "detect")

SET(SRC
		Interfaces.hpp

		detect_markers.cpp
		Interfaces.cpp
		)

ADD_DEFINITIONS(-Wall)


ADD_EXECUTABLE(${TARGET} ${SRC})
TARGET_LINK_LIBRARIES(${TARGET} aruco maximilian)
