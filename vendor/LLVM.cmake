

# LLVM Configuration
if (ENABLE_LLVM)

    # find external LLVM library
    if (USE_EXTERNAL_LLVM)
        set(LLVM_PATH ${LLVM_PROJECT_ROOT}/build/lib/cmake/llvm CACHE STRING "path to llvm lib")
        set(LLVM_DIR ${LLVM_PATH})

        message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
        find_package(LLVM REQUIRED CONFIG)
        message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
        message(STATUS "llvm include dir ${LLVM_INCLUDE_DIRS}")

    endif ()

    # add LLVM definitions
    add_definitions(${LLVM_DEFINITIONS})

    # set $LLVMLIBS variable
    # object option target ipo ipa
    set(llvm_components support core irreader bitreader analysis mc native)
    llvm_map_components_to_libnames(LLVMLIBS ${llvm_components})
endif()