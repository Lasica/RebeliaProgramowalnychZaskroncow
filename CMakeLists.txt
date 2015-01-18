project(rpz)
cmake_minimum_required(VERSION 2.8)
find_package(Boost COMPONENTS system thread filesystem unit_test_framework serialization REQUIRED)
find_package(Lua REQUIRED)

enable_testing()

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/src
	${rpz_SOURCE_DIR}/src
	)

set(Boost_USE_MULTITHREADED ON)
set(CMAKE_CXX_CREATE_SHARED_LIBRARY ON)
set(CMAKE_CXX_CREATE_SHARED_MODULE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) # zeby exec byl tez w build/, a nie tylko build/src
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic -Wextra -std=c++11")
#install(TARGETS rpz RUNTIME DESTINATION bin

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
