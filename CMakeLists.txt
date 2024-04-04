cmake_minimum_required(VERSION 3.27)
project(table-recognizer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

message("OpenCV_DIR is '$ENV{OpenCV_DIR}'")

find_package(OpenCV REQUIRED)

# Adding cpp-httplib library ==================================================
FetchContent_Declare(httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
  GIT_TAG v0.15.3
  GIT_SHALLOW TRUE
)
set(HTTPLIB_COMPILE ON)
FetchContent_MakeAvailable(httplib)
# =============================================================================

set(BUILD_COMPONENT "BOTH" CACHE STRING "Component to build (CLIENT, SERVER, or BOTH)")

if(${BUILD_COMPONENT} STREQUAL "CLIENT" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(client)
endif()

if(${BUILD_COMPONENT} STREQUAL "SERVER" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(server)
endif()
