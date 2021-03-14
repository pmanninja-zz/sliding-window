server: server.o 
    g++ server.o -o server

client: client.o 
    g++ client.o -o client

server.o: server.cpp
    g++ -C server.cpp

client.o: client.cpp
    g++ -C client.cpp

clean:
    rm *.o server client