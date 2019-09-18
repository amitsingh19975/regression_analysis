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

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
	add_subdirectory(test)
endif()
