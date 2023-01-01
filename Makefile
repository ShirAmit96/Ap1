all : server client
server: server.cpp
	g++ -std=c++11 -o server server.cpp server_side.cpp server_side.h
client: client.cpp
	g++ -std=c++11 -o client client.cpp client.h
clean:
	rm client server



