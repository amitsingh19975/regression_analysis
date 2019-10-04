# Disable in-source builds to prevent source tree corruption
if (" ${CMAKE_SOURCE_DIR} " STREQUAL " ${CMAKE_BINARY_DIR} ")
message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
You should create a seperate directory for build files.
")
endif()

find_library(GSL_LIB gsl)
if (NOT GSL_LIB)
message(FATAL_ERROR "
FATAL: GSL library not found.
Make sure GSL is installed.
")
endfi()

cmake_minimum_required(VERSION 3.10)

project(regression_model
	VERSION 0.1
	DESCRIPTION "Regression library for Machine Learning"
	LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_C_EXTENTSIONS OFF)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	
	include(CTest)

	find_package(Doxygen)

	if(DOXYGEN_FOUND)
		add_subdirectory(docs)
	else()
		message( STATUS "Doxygen not found")
	endif()

endif()

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
	add_subdirectory(test)
endif()
