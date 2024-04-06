set(SRC_DIR src)
set(INC_DIR ..)

# Creating a static library from sources
file(GLOB SOURCES "${SRC_DIR}/*.cc")
list(REMOVE_ITEM SOURCES "${SOURCE_DIR}/main.cc")
add_library(client_sources STATIC ${SOURCES})
target_include_directories(client_sources PUBLIC ${INC_DIR} ${OpenCV_INCLUDE_DIRS})

# Creating executable file for main.cpp
add_executable(client_main ${SRC_DIR}/main.cc)
target_link_libraries(client_main client_sources ${OpenCV_LIBS} httplib)
