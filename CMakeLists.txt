cmake_minimum_required (VERSION 2.6)
project (DistributedComputing)

# The version number.
set (Test_VERSION_MAJOR 1)
set (Test_VERSION_MINOR 0)

# A convenience variable:
set(LLVM_ROOT "" CACHE PATH "Root of LLVM install.")

# A bit of a sanity check:
if( NOT EXISTS ${LLVM_ROOT}/include/llvm )
message(FATAL_ERROR "LLVM_ROOT (${LLVM_ROOT}) is not a valid LLVM install")
endif()

# We incorporate the CMake features provided by LLVM:
list(APPEND CMAKE_MODULE_PATH  "${LLVM_ROOT}/share/llvm/cmake")
include(LLVMConfig)


# geting the git version to stamp files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules/")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/in/TestConfig.h.in"
  "${PROJECT_BINARY_DIR}/include/TestConfig.h"
  )
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h


# Now set the header and library paths:
include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )
add_definitions( ${LLVM_DEFINITIONS} )

include_directories ("${PROJECT_BINARY_DIR}/include/")
include_directories ("src/libs/GitSHA1")
add_subdirectory(src)

