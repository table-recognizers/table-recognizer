cmake_minimum_required(VERSION 3.27)
project(table-recognizer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("OpenCV_DIR is '$ENV{OpenCV_DIR}'")

find_package(OpenCV REQUIRED)

add_subdirectory(client)
