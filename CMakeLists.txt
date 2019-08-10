cmake_minimum_required(VERSION 3.6)
project(area)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

include_directories (include)

set(SOURCE_FILES
        src/main.cpp
        src/polygon.cpp
        include/polygon.h
        include/utils.h
)

add_executable(area ${SOURCE_FILES})
target_link_libraries(area ${OpenCV_LIBS})