cmake_minimum_required(3.12 FATAL_ERROR)

project(eastl-polyalloc LANGUAGE CXX)

find_file(EASTL_HEADER_VECTOR vector.h PATH_SUFFIXES EASTL)
if(NOT EASTL_HEADER_VECTOR)
	message(FATAL_ERROR "EASTL not found")
endif()
get_filename_component(EASTL_HEADER ${EASTL_HEADER_VECTOR} DIRECTORY)
get_filename_component(EASTL_HEADER ${EASTL_HEADER} DIRECTORY)

add_library(eastl-polyalloc INTERFACE)
target_include_directories(eastl-polyalloc INTERFACE ${EASTL_HEADER})

include(GNUInstallDirs)

install(
    TARGETS eastl-polyalloc CONFIG eastl-polyalloc-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/
)

install(
    EXPORT eastl-polyalloc-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/eastl-polyalloc
    NAMESPACE eastl::
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
    FILES_MATCHING PATTERN "*.hpp*"
)
