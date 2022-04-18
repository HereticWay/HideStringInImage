cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME "HideStringInImage")
set(PROJECT_VERSION "0.1.0")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

#include(CTest)
#enable_testing()

set(PROJECT_SRC "${PROJECT_SOURCE_DIR}/src")


set(zlib lib/zlib)
file(GLOB
        zlib_files
        "${zlib}/**.c")
add_library(zlib ${zlib_files})


set(libpng lib/libpng)
file(GLOB
        libpng_files
        "${libpng}/**.c")
add_library(libpng ${libpng_files})


file(GLOB
        source_files
        "${PROJECT_SRC}/**.c")
add_executable(${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        zlib
        libpng)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${zlib}"
        "${libpng}")


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
