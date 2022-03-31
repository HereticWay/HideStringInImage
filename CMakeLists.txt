cmake_minimum_required(VERSION 3.0.0)
project(HideStringInImage VERSION 0.1.0)

include(CTest)
enable_testing()

set(LIBPNG_PATH /usr/include/libpng16/)

include_directories(${LIBPNG_PATH})

add_executable(HideStringInImage ${PROJECT_SOURCE_DIR}/src/main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
