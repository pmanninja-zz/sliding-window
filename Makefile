all: client server

client: src/Protocol.h src/Protocol.cpp src/client.cpp
	g++ -std=c++11 -pthread src/Protocol.cpp src/client.cpp -o client

server: src/Protocol.h src/Protocol.cpp src/server.cpp
	g++ -std=c++11 -pthread src/Protocol.cpp src/server.cpp -o server

clean: client server
	rm -f client server
