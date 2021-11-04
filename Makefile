all: clear server client

server:
	g++ -pthread src/server/server.cpp src/socket/socket.cpp src/server.cpp -o build/TCP-server
client:
	g++ src/socket/socket.cpp src/client/client.cpp src/client.cpp -o build/TCP-client
clear:
	rm -f client && rm -f build/TCP-server && rm build/TCP-client
run-server:
	./build/TCP-server
run-client:
	./build/TCP-client