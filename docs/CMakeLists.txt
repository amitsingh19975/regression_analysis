option(BUILD_DOC "Build Documentation" ON)

set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/../docs/config")
set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxygen")

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

message("Building documentaion")

add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation"
        VERBATIM)



