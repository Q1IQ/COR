
cmake_minimum_required(VERSION 3.15)
project(COR)

if (UNIX)
    # todo: target_compile_features
    # https://enginetrouble.net/2015/11/trying-to-link-clang-libtooling-into-my-program.html
    # fix: Undefined symbols: clang::tooling::FrontendActionFactory
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
endif ()

import_cor_files(COR_SOURCE_FILES)

add_executable(cor cor_main.cpp)
use_clang_library(cor)
target_link_libraries(cor PUBLIC lib_cor)
