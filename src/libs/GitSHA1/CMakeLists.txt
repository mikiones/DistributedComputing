configure_file("${CMAKE_SOURCE_DIR}/in/GitSHA1.cpp.in" "${CMAKE_BINARY_DIR}/src/libs/GitSHA1/GitSHA1.cpp" @ONLY)

add_library(GitSHA1  "${CMAKE_CURRENT_BINARY_DIR}/GitSHA1.cpp" GitSHA1.h)
include_directories ("${CMAKE_CURRENT_BINARY_DIR}")
