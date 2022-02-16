cmake_minimum_required(VERSION 3.15)
project(COR)

# project declarations
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# configuration
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_definitions(-DYY_NO_UNISTD_H)
endif ()

# path to llvm project root
set(LLVM_PROJECT_ROOT /Users/apple/LLVM/llvm-project-llvmorg-12.0.0)

# options group: enable the targets related to *
option(ENABLE_LLVM "enable llvm related targets" ON)
option(ENABLE_CLANG "enable clang related targets" ON)

# options group: use the external library * if the corresponding switch is set to true
option(USE_EXTERNAL_LLVM "use an external LLVM library" ON)
option(USE_EXTERNAL_CLANG "use an external CLANG library" ON)

message("USING CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})

# include library configurations
include(vendor/LLVM.cmake)
include(vendor/Clang.cmake)

# source files (implementations)
add_subdirectory(src)
