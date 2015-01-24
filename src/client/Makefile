client: client_main.o main.o Address.o 
	g++ client.o client_main.o  Address.o -lboost_system -o client

client_main.o: client_main.cpp
	g++ client_main.cpp -o client_main.o

main.o: main.cpp
	g++ main.cpp -o main.o
Address.o: Address.cpp
	g++ Address.cpp -o Address.o
