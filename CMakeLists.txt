cmake_minimum_required(VERSION 3.0.0)
project(
	"HideStringInImage"
	VERSION "0.1.0"
	LANGUAGES C
)

#include(CTest)
#enable_testing()

set(zlib "${PROJECT_SOURCE_DIR}/lib/zlib")
set(libpng "${PROJECT_SOURCE_DIR}/lib/libpng")
set(PROJECT_SRC "${PROJECT_SOURCE_DIR}/src")


add_subdirectory(${zlib} EXCLUDE_FROM_ALL)


set(PNG_SHARED       OFF CACHE BOOL "disable libpng shared libraries"  FORCE)
set(PNG_EXECUTABLES  OFF CACHE BOOL "disable libpng executables"       FORCE)
set(PNG_TESTS        OFF CACHE BOOL "disable libpng tests"             FORCE)
set(PNG_STATIC       ON  CACHE BOOL "enable libpng static libraries"   FORCE)
set(PNG_BUILD_ZLIB   ON  CACHE BOOL "zlib is built by ourselves"       FORCE)
set(SKIP_INSTALL_ALL ON  CACHE BOOL "skip libpng install"              FORCE)
#set(ZLIB_LIBRARY "${zlib}")
#set(ZLIB_INCLUDE_DIR "${zlib}")
add_subdirectory(${libpng} EXCLUDE_FROM_ALL)


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
