file(GLOB_RECURSE SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
get_filename_component(current_dir ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_library(${current_dir} ${SRC})
