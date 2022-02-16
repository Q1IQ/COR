import_cor_files(COR_SOURCE_FILES)

add_all_library(lib_cor)
target_sources(lib_cor INTERFACE ${COR_SOURCE_FILES})

target_link_libraries(lib_cor INTERFACE )

target_include_directories(lib_cor INTERFACE include)