
cmake_minimum_required(VERSION 3.1)
project(espeedy-esp)

add_subdirectory(lib)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

add_library(espeedy-esp
        ${SRC}
)

target_link_libraries(espeedy-esp
        PUBLIC arduino-esp32
)
