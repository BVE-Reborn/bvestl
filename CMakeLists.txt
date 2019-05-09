cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(bvestl LANGUAGES CXX)

# Find EASTL
find_file(EASTL_HEADER_VECTOR vector.h PATH_SUFFIXES EASTL)
if(NOT EASTL_HEADER_VECTOR)
	message(FATAL_ERROR "EASTL not found")
endif()
get_filename_component(EASTL_HEADER ${EASTL_HEADER_VECTOR} DIRECTORY)
get_filename_component(EASTL_HEADER ${EASTL_HEADER} DIRECTORY)

add_library(bvestl INTERFACE)
target_include_directories(bvestl INTERFACE ${EASTL_HEADER})

include(GNUInstallDirs)

install(
    TARGETS bvestl EXPORT bvestl-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/
)

install(
    EXPORT bvestl-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/bvestl
    NAMESPACE bvestl::
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
    FILES_MATCHING PATTERN "*.h*"
)
