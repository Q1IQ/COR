
# CLANG Configuration
if (ENABLE_CLANG)

    # find external Clang library
    if (USE_EXTERNAL_CLANG)
        set(CLANG_PATH ${LLVM_PROJECT_ROOT}/build/lib/cmake/clang CACHE STRING "path to clang lib")
        set(Clang_DIR ${CLANG_PATH})

        message(STATUS "Using CLANGConfig.cmake in: ${Clang_DIR}")
        find_package(Clang REQUIRED CONFIG)
    endif ()

    # add CLANG definitions
    add_definitions(${CLANG_DEFINITIONS})

    # set ClangLIBS variable
    set(ClangLIBS clangTooling clangBasic clangAST clangFrontend)

    # description: include clang directories
    # param:
    #     target
    function(include_clang_directories target)
        target_include_directories(${target} INTERFACE ${LLVM_INCLUDE_DIRS})
        target_include_directories(${target} INTERFACE ${CLANG_INCLUDE_DIRS})
    endfunction()

    # description: use clang library
    # param:
    #     target
    function(use_clang_library target)
        cmake_parse_arguments(Link "" "" "ClangLibs;LLVMLibs;ClangLibsA;LLVMLibsA" ${ARGN})

        if (NOT Link_ClangLibs)
            set(Link_ClangLibs ${ClangLIBS})
        endif ()

        if (NOT Link_LLVMLibs)
            set(Link_LLVMLibs ${LLVMLIBS})
        endif ()

        if (ClangLibsA)
            list(APPEND Link_ClangLibs ${ClangLibsA})
        endif ()

        if (LLVMLibsA)
            list(APPEND Link_LLVMLibs ${LLVMLibsA})
        endif ()

        include_clang_directories(${target})

        if (MSVC)
            # see review https://reviews.llvm.org/D56329
            # ignore "warning LNK4199: /DELAYLOAD:shell32.dll ignored; no imports found from shell32.dll"
            target_link_libraries(${target} INTERFACE "-ignore:4199")
        endif ()

        target_link_libraries(${target} INTERFACE ${Link_ClangLibs} ${Link_LLVMLibs})
    endfunction()

endif()
