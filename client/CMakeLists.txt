set(SRC_DIR src)
set(INC_DIR ..)

file(GLOB SOURCES "${SRC_DIR}/*.cc")
add_executable(client_main ${SOURCES})
target_include_directories(client_main PUBLIC ${INC_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(client_main ${OpenCV_LIBS})
