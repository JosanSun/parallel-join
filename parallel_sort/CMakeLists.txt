set(DEBUG_FLAGS "-g -O0 -Wall -fopenmp -D_GLIBCXX_PARALLEL")
set(RELEASE_FLAGS "-O3 -fopenmp -D_GLIBCXX_PARALLEL")

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
get_filename_component(current_dir ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_library(${current_dir} ${SRC})
