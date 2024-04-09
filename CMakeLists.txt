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

# Adding rapidjson library ====================================================
FetchContent_Declare(rapidjson
  GIT_REPOSITORY https://github.com/Tencent/rapidjson
  GIT_TAG v1.1.0
  GIT_SHALLOW TRUE
)
FetchContent_GetProperties(rapidjson)
if(NOT rapidjson_POPULATED)
  FetchContent_Populate(rapidjson)
  add_library(rapidjson INTERFACE IMPORTED)
  target_include_directories(rapidjson INTERFACE ${rapidjson_SOURCE_DIR}/include)
endif()

# Adding googletest library ===================================================
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.14.0
  GIT_SHALLOW TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(BUILD_COMPONENT "BOTH" CACHE STRING "Component to build (CLIENT, SERVER, or BOTH)")

add_subdirectory(utils)

if(${BUILD_COMPONENT} STREQUAL "CLIENT" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(client)
endif()

if(${BUILD_COMPONENT} STREQUAL "SERVER" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(server)
endif()
