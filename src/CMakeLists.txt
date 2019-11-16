file(GLOB_RECURSE HEADER_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/lib/include/*.h")
file(GLOB_RECURSE CFILE_LIST CONFIGURE DEPENDS "${regression_model_SOURCE_DIR}/lib/*.c")

#add_library(${HEADER_LIST})

add_executable(regression_model main.c ${CFILE_LIST})

target_link_libraries(regression_model gsl gslcblas m)

source_group(TREE "${PROJECT_SOURCE_DIR}/lib/include" PREFIX "Header Files" FILES ${HEADER_LIST} )

