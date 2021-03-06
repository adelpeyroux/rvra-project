cmake_minimum_required(VERSION 3.2.0)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMAKE_BUILD_TYPE: Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)
set (CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_subdirectory(ext/aruco)
INCLUDE_DIRECTORIES(ext/aruco/src)

add_subdirectory(ext/Maximilian)
INCLUDE_DIRECTORIES(ext/Maximilian)

INCLUDE_DIRECTORIES(include)

SET(TARGET "ReactCamera")

SET(SRC
		include/MarkerGraph.hpp
		include/Nodes.hpp
		include/AudioNode.hpp
		include/OscNode.hpp
		include/DestinationNode.hpp
		include/xMarker.hpp
		include/Interfaces.hpp
		include/MiscConsts.hpp
                include/AmNode.hpp
                include/NoiseNode.hpp
                include/NumericalNode.hpp
                include/FmNode.hpp
                include/SampleNode.hpp

		src/main.cpp
		src/MarkerGraph.cpp
		src/DestinationNode.cpp
		src/OscNode.cpp
                src/xMarker.cpp
                src/Interfaces.cpp
                src/AmNode.cpp
                src/FmNode.cpp
                src/NoiseNode.cpp
                src/NumericalNode.cpp
                src/SampleNode.cpp)

ADD_DEFINITIONS(-Wall -g -pg)
add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data")

ADD_EXECUTABLE(${TARGET} ${SRC})
TARGET_LINK_LIBRARIES(${TARGET} aruco maximilian)
