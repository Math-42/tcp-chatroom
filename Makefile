all: server client

server:
	g++ src/server.cpp src/socket/socket.cpp src/server/server.cpp -pthread -o build/TCP-server
client:
	g++ src/client.cpp src/socket/socket.cpp src/client/client.cpp -o build/TCP-client
clear:
	rm -r build/*
init:
	mkdir build
run-server:
	./build/TCP-server
run-client:
	./build/TCP-client