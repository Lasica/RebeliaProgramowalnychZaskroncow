set(LIB_SOURCES
    server/Client.cpp
    server/ClientsRegister.cpp
    shared/ChatEntry.cpp
    shared/ChatHistory.cpp
    shared/ClientList.cpp
    shared/GameRoom.cpp
    shared/GameRoomList.cpp
    shared/Resource.cpp
		shared/ResourceFactory.cpp
	)

set(LIB_HEADERS
	luacore/LuaInterpreter.h
	test/TestTemplate.h
	server/ClientsRegister.hpp
	server/Client.hpp
	shared/ClientList.h
	shared/ChatEntry.h
	shared/Subject.h
	shared/ClientListRaw.h
	shared/Resource.h
	shared/GameRoomListRaw.h
	shared/GameRoomRaw.h
	shared/GameRoom.h
	shared/ChatHistory.h
	shared/Observer.h
	shared/ChatHistoryRaw.h
	shared/ResourceFactory.h
	shared/GameRoomList.h
	shared/ChatEntryRaw.h
	)

add_library( PROJECT_LIBRARY ${LIB_SOURCES} ${LIB_HEADERS} )

set(LIBRARIES
	  ${LUA_LIBRARY} ${LUA_CORE_SRC} 
  	-llog4cpp 
  	-pthread 
		${Boost_LIBRARIES}
		#${Boost_FILESYSTEM_LIBRARY} 
		#${Boost_SYSTEM_LIBRARY} 
		#${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		#${Boost_SERIALIZATION}
	)

#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_executable(server server/server.cpp)
target_link_libraries(server ${LIBRARIES} PROJECT_LIBRARY )

add_executable(client client/client.cpp)
target_link_libraries(client ${LIBRARIES} PROJECT_LIBRARY )


#I like to keep test files in a separate source directory called test
file(GLOB TEST_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   test/*.cpp)

#Run through each source
foreach(testSrc ${TEST_SRC})
	MESSAGE( STATUS "REGISTERED TEST:  " ${testSrc})
  #Extract the filename without an extension (NAME_WE)
  get_filename_component(testName ${testSrc} NAME_WE)

  #Add compile target
	add_executable(${testName} ${testSrc})

  #link to Boost libraries AND your targets and dependencies
	target_link_libraries(${testName} ${LIBRARIES} PROJECT_LIBRARY)

  #I like to move testing binaries into a testBin directory
	set_target_properties(${testName} PROPERTIES 
		RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/testBin )

  #Finally add it to test execution - 
  #Notice the WORKING_DIRECTORY and COMMAND
  add_test(NAME ${testName} 
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/testBin 
		COMMAND ${CMAKE_BINARY_DIR}/testBin/${testName} )
endforeach(testSrc)
