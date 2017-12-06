# Install script for directory: D:/SourceTree/rvra-project/ext/aruco/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "main" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/SourceTree/rvra-project/VSSolutions/Release/Debug/aruco201.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/SourceTree/rvra-project/VSSolutions/Release/Release/aruco201.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/SourceTree/rvra-project/VSSolutions/Release/MinSizeRel/aruco201.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/SourceTree/rvra-project/VSSolutions/Release/RelWithDebInfo/aruco201.lib")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "main" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/SourceTree/rvra-project/VSSolutions/Release/Debug/aruco201.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/SourceTree/rvra-project/VSSolutions/Release/Release/aruco201.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/SourceTree/rvra-project/VSSolutions/Release/MinSizeRel/aruco201.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/SourceTree/rvra-project/VSSolutions/Release/RelWithDebInfo/aruco201.dll")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "main" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aruco" TYPE FILE FILES
    "D:/SourceTree/rvra-project/ext/aruco/src/ar_omp.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/aruco.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/cameraparameters.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/checkrectcontour.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/cvdrawingutils.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/dictionary.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/exports.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/ippe.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/levmarq.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/marker.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/markerdetector.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/markerlabeler.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/markermap.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/posetracker.h"
    "D:/SourceTree/rvra-project/ext/aruco/src/markerlabelers/dictionary_based.h"
    )
endif()

