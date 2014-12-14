set(rpz_SRCS
    shared/ChatEntry.cpp
    shared/ChatHistory.cpp
    shared/ClientList.cpp
    shared/GameRoom.cpp
    shared/GameRoomList.cpp
    shared/Resource.cpp
		#    shared/Subject.cpp
		shared/ResourceFactory.cpp
    main.cpp
	)

add_executable(rpz ${rpz_SRCS})
target_link_libraries(rpz ${LUA_LIBRARY} ${LUA_CORE_SRC} -llog4cpp -pthread -lboost_system)
