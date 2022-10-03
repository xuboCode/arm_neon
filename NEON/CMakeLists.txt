cmake_minimum_required(VERSION 3.8.2)

project(test_neon)

set(OpenCV_DIR /opt/rk3568_sdk/thirdparty/opencv/lib/cmake/opencv4)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

SET(SRC_LIST readImage.cpp）
ADD_EXECUTABLE(test_neon ${SRC_LIST})



