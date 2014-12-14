set(rpz_SRCS
    main.cpp
	)

add_executable(rpz ${rpz_SRCS})
target_link_libraries(rpz ${LUA_LIBRARY} ${LUA_CORE_SRC} -llog4cpp -pthread)

