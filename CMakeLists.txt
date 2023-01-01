cmake_minimum_required(VERSION 3.11)

project(fireworks)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TRACY_ENABLE ON CACHE BOOL "Enable tracy profiler")
set(TRACY_ON_DEMAND ON CACHE BOOL "")
add_subdirectory(external/tracy)

set(SRC_FILES
    src/particle.c
    src/main.c)

add_executable(fireworks ${SRC_FILES})
target_link_libraries(fireworks PUBLIC TracyClient ncurses)
target_include_directories(fireworks PUBLIC ./include)


