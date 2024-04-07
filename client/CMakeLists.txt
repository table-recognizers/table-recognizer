set(SRC_DIR src)
set(INC_DIR ..)
set(TEST_DIR test)

# Creating a static library from sources
file(GLOB SOURCES "${SRC_DIR}/*.cc")
get_filename_component(MAIN_FILE "${SRC_DIR}/main.cc" ABSOLUTE)
list(REMOVE_ITEM SOURCES ${MAIN_FILE})
add_library(client_sources STATIC ${SOURCES})
target_include_directories(client_sources PUBLIC ${INC_DIR} ${OpenCV_INCLUDE_DIRS})

# Creating executable file for main.cpp
add_executable(client_main ${SRC_DIR}/main.cc)
target_link_libraries(client_main client_sources ${OpenCV_LIBS} httplib)

# Add tests
enable_testing()
include(GoogleTest)
file(GLOB TEST_SOURCES "${TEST_DIR}/*.cc")

foreach(TEST_SRC ${TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_SRC})
  target_link_libraries(${TEST_NAME} client_sources gtest_main)
  gtest_discover_tests(${TEST_NAME})
  list(APPEND TEST_TARGETS ${TEST_NAME})
endforeach()

add_custom_target(run_tests ALL
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${TEST_TARGETS})
