cmake_minimum_required (VERSION 2.6)
project (DistributedComputing)

# The version number.
set (Test_VERSION_MAJOR 1)
set (Test_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/in/TestConfig.h.in"
  "${PROJECT_BINARY_DIR}/include/TestConfig.h"
  )
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}/include/")

add_executable(Test  ${PROJECT_SOURCE_DIR}/src/test/test.cxx)
