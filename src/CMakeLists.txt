file(GLOB_RECURSE HEADER_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE CFILE_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/include/*.c")
#set(HEADER_LIST "${DAA_SOURCE_DIR}/include/daa.hpp")

#add_library(${HEADER_LIST})

#target_link_libraries( )

add_executable(regression_model main.c ${CFILE_LIST})

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST} )

