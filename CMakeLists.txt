cmake_minimum_required(VERSION 3.0.0)
project(HideStringInImage VERSION 0.1.0)

include(CTest)
enable_testing()

# Set libpng paths
set(LIBPNG_INCLUDE_PATH /usr/include/libpng16/)
set(LIBPNG_LIB /usr/lib/libpng16.so)

set(PROJECT_SRC ${PROJECT_SOURCE_DIR}/src)

# Include thingies
include_directories(${PROJECT_SRC} ${LIBPNG_PATH})

add_executable(HideStringInImage ${PROJECT_SRC}/main.c ${PROJECT_SRC}/message_hider/message_hider.c src/errors.h)
target_link_libraries(HideStringInImage ${LIBPNG_LIB}) # Here we link libpng to our project

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
