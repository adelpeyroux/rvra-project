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

INCLUDE_DIRECTORIES(include)

SET(TARGET "detect")

SET(SRC
		include/AudioGraph.hpp
                include/MarkerGraph.hpp
		include/AudioNode.hpp
                include/OscNode.hpp
                include/DestinationNode.hpp
		include/Interfaces.hpp
                include/xMarker.hpp
                include/MiscConsts.hpp

		src/detect_markers.cpp
		src/AudioGraph.cpp
                src/MarkerGraph.cpp
		src/AudioNode.cpp
                src/DestinationNode.cpp
                src/OscNode.cpp
                src/Interfaces.cpp
                src/xMarker.cpp)


SET(SRC_INTERFACE_TEST
		include/Interfaces.hpp

		src/Interfaces.cpp
		src/Interfaces_Tests.cpp)

ADD_DEFINITIONS(-Wall)


ADD_EXECUTABLE(${TARGET} ${SRC})
TARGET_LINK_LIBRARIES(${TARGET} aruco maximilian)


ADD_EXECUTABLE(Interface_Test ${SRC_INTERFACE_TEST})
TARGET_LINK_LIBRARIES(Interface_Test ${OpenCV_LIBS})
