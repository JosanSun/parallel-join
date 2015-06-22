cmake_minimum_required (VERSION 2.8)

project(ParallelJoin)
set(Project_VERSION_MAJOR 1)
set(Project_VERSION_MAJOR 0)

set(CMAKE_CXX_COMPILER icpc)
set(DEBUG_FLAGS "-std=c++11 -g -O0 -Wall -pthread")
set(RELEASE_FLAGS "-std=c++11 -Ofast -pthread")

set(CMAKE_CXX_FLAGS ${RELEASE_FLAGS})
set(CMAKE_C_FLAGS ${RELEASE_FLAGS})

set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})
set(CMAKE_C_FLAGS_DEBUG ${DEBUG_FLAGS})

set(CMAKE_CONFIGURATION_TYPES Debug Release)

#set(current_lib serial_sort)
#set(current_lib parallel_sort)
#set(current_lib serial_hash)
set(current_lib parallel_hash)
include_directories(${current_lib})
add_subdirectory(${current_lib})
set(EXTRA_LIBS ${EXTRA_LIBS} ${current_lib})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
set(TARGET join)
add_executable(${TARGET} ${SRC})
target_link_libraries(${TARGET} ${EXTRA_LIBS})
