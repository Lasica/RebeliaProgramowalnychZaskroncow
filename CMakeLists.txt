project(rpz)
cmake_minimum_required(VERSION 2.6)
#find_package(Lua REQUIRED)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/src
	${rpz_SOURCE_DIR}/src
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic -Wextra -std=c++11")
#install(TARGETS rpz RUNTIME DESTINATION bin)
add_subdirectory(src)
