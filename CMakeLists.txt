cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(eastl-polyalloc LANGUAGES CXX)

find_file(EASTL_HEADER_VECTOR vector.h PATH_SUFFIXES EASTL)
if(NOT EASTL_HEADER_VECTOR)
	message(FATAL_ERROR "EASTL not found")
endif()
get_filename_component(EASTL_HEADER ${EASTL_HEADER_VECTOR} DIRECTORY)
get_filename_component(EASTL_HEADER ${EASTL_HEADER} DIRECTORY)

add_library(polyalloc INTERFACE)
target_include_directories(polyalloc INTERFACE ${EASTL_HEADER})

include(GNUInstallDirs)

install(
    TARGETS polyalloc EXPORT eastl-polyalloc-config
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
    FILES_MATCHING PATTERN "*.h*"
)
