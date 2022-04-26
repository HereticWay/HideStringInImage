cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME "HideStringInImage")
set(PROJECT_VERSION "0.1.0")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

#include(CTest)
#enable_testing()

set(zlib "${PROJECT_SOURCE_DIR}/lib/zlib")
set(libpng "${PROJECT_SOURCE_DIR}/lib/libpng")
set(PROJECT_SRC "${PROJECT_SOURCE_DIR}/src")
set(ZLIB_LIBRARY "${zlib}")
set(ZLIB_INCLUDE_DIR "${zlib}")

set(PNG_STATIC ON)
add_subdirectory(${libpng})
add_subdirectory(${zlib})

file(GLOB
        source_files
        "${PROJECT_SRC}/*.c"
        "${PROJECT_SRC}/message_hider/*.c")
add_executable(${PROJECT_NAME} ${source_files})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        "${PROJECT_SRC}"
        "${zlib}"
        "${libpng}")

target_link_libraries(${PROJECT_NAME} png_static zlibstatic)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
