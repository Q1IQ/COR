
cmake_minimum_required(VERSION 3.15)
project(COR)

function(add_all_library library)
    add_library(${library} INTERFACE)
    use_clang_library(${library} ${ARGN})
endfunction()

include_directories(.)

add_subdirectory(COR)

# import fps, common source file
import_cor_files(COR_SOURCE_FILES)

