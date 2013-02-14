include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )
add_definitions( ${LLVM_DEFINITIONS} )

llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES core)
add_executable (Module1 module1.cxx)
target_link_libraries (Module1 GitSHA1 ${REQ_LLVM_LIBRARIES})

