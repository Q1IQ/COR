macro(import_cor_files files_var_ref)
    file(GLOB ${files_var_ref} ${CMAKE_SOURCE_DIR}/src/lib/COR/**.cpp)
endmacro()
