include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )
add_definitions( ${LLVM_DEFINITIONS} )

llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES core jit interpreter nativecodegen bitwriter )
add_executable (JIT jit.cxx)
target_link_libraries (JIT GitSHA1 ${REQ_LLVM_LIBRARIES})

