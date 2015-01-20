set(LIB_SOURCES
    client/client_main.cpp
		server/Address.cpp
	server/PacketQueueAdapter.cpp
		server/AddressRegister.cpp
    server/Client.cpp
    #server/ClientDataRaw.cpp
    server/ClientsRegister.cpp
    server/GameRoomsRegister.cpp
		#server/Logger.cpp
		server/Packet_handler.cpp
    server/Server.cpp
    server/server_main.cpp
		shared/ChatEntryRaw.cpp
    shared/ChatRegister.cpp
		shared/constants.cpp
    shared/GameRoom.cpp
    shared/GameRoomRaw.cpp
    shared/Packet.cpp
    shared/TcpConnection.cpp
    shared/Observer.cpp
	)

set(LIB_HEADERS
 #luacore/LuaInterpreter.hpp
	server/Address.hpp
	server/AddressRegister.hpp
	server/Client.hpp
        server/ClientDataRaw.hpp
        server/ClientsRegister.hpp
        server/GameRoomsRegister.hpp
	server/Packet_handler.hpp
	server/PacketQueueAdapter.hpp
	#server/Logger.hpp
	server/Server.hpp
	server/ServerResources.hpp
	shared/ChatEntryRaw.hpp
	shared/ChatRegister.hpp
        shared/GameRoom.hpp
        shared/GameRoomRaw.hpp
        shared/HandshakeRaw.hpp
	shared/Observer.hpp
	shared/Packet.hpp
	shared/Resource.hpp
	shared/Subject.hpp
	shared/TcpConnection.hpp
  shared/typedefinitions.hpp
	)

add_library( PROJECT_LIBRARY ${LIB_SOURCES} ${LIB_HEADERS} )

set(LIBRARIES
	  ${LUA_LIBRARY} ${LUA_CORE_SRC} 
  	-pthread 
		${Boost_LIBRARIES}
		${Boost_FILESYSTEM_LIBRARY} 
		${Boost_SYSTEM_LIBRARY} 
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		${Boost_SERIALIZATION}
		${Boost_THREAD}
)	

#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_executable(server server/server_main.cpp)
target_link_libraries(server ${LIBRARIES} PROJECT_LIBRARY )

add_executable(client client/client_main.cpp)
target_link_libraries(client ${LIBRARIES} PROJECT_LIBRARY )

#add_executable(fake_server server/fake_server_main.cpp)
#target_link_libraries(fake_server ${LIBRARIES} PROJECT_LIBRARY )


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
