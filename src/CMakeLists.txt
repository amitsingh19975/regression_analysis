<<<<<<< HEAD
file(GLOB_RECURSE HEADER_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE CFILE_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/include/*.c")
=======
file(GLOB_RECURSE HEADER_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/lib/include/*.h")
file(GLOB_RECURSE CFILE_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/lib/*.c")
>>>>>>> fe9239b81930f6abec3dd5655cd2805f8e24c0a2
#set(HEADER_LIST "${DAA_SOURCE_DIR}/include/daa.hpp")

# add_library(${HEADER_LIST})

add_executable(regression_model main.c ${CFILE_LIST})

target_link_libraries(regression_model gsl)

source_group(TREE "${PROJECT_SOURCE_DIR}/lib/include" PREFIX "Header Files" FILES ${HEADER_LIST} )

