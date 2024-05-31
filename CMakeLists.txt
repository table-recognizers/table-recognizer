cmake_minimum_required(VERSION 3.27)
project(table-recognizer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

# Adding opencv library =======================================================
find_package(OpenCV REQUIRED)
message("[${PROJECT_NAME}] opencv library has been populated")

# Adding cpp-httplib library ==================================================
find_package(httplib REQUIRED)
message("[${PROJECT_NAME}] httplib library has been populated")

# Adding rapidjson library ====================================================
FetchContent_Declare(rapidjson
  GIT_REPOSITORY https://github.com/Tencent/rapidjson
  GIT_TAG v1.1.0
  GIT_SHALLOW TRUE
)
FetchContent_GetProperties(rapidjson)

if(NOT rapidjson_POPULATED)
  FetchContent_Populate(rapidjson)
  message("[${PROJECT_NAME}] rapidjson library has been populated")
endif()

# Adding googletest library ===================================================
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG v1.14.0
  GIT_SHALLOW TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
message("[${PROJECT_NAME}] googletest library has been populated")

# Adding tesseract library ====================================================
find_package(leptonica)
find_package(Tesseract REQUIRED)
FetchContent_Declare(tessdata
  GIT_REPOSITORY https://github.com/tesseract-ocr/tessdata
  GIT_TAG 4.1.0
  GIT_SHALLOW TRUE
)
FetchContent_GetProperties(tessdata)
if(NOT tessdata_POPULATED)
  FetchContent_Populate(tessdata)
endif()
add_compile_definitions(TESSDATA_PATH="${tessdata_SOURCE_DIR}")
message("[${PROJECT_NAME}] tesseract library has been populated")

# Adding openxlsx library =====================================================
find_package(OpenXLSX REQUIRED)
message("[${PROJECT_NAME}] openxlsx library has been populated")

# Adding project components ===================================================
set(BUILD_COMPONENT "BOTH" CACHE STRING "Component to build (CLIENT, SERVER, or BOTH)")
add_subdirectory(utils)

if(${BUILD_COMPONENT} STREQUAL "CLIENT" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(client)
endif()

if(${BUILD_COMPONENT} STREQUAL "SERVER" OR ${BUILD_COMPONENT} STREQUAL "BOTH")
  add_subdirectory(server)
endif()
