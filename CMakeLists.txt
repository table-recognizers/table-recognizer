cmake_minimum_required(VERSION 3.27)
project(table-recognizer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("OpenCV_DIR is '$ENV{OpenCV_DIR}'")

find_package(OpenCV REQUIRED)

set(BUILD_COMPONENT "BOTH" CACHE STRING "Component to build (CLIENT, SERVER, or BOTH)")

if(${BUILD_COMPONENT} STREQUAL "CLIENT" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(client)
endif()

if(${BUILD_COMPONENT} STREQUAL "SERVER" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(server)
endif()
