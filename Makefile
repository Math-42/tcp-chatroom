all:server client

server:
	g++ src/server.cpp src/socket/socket.cpp src/server/server.cpp -pthread -o build/TCP-server
client:
	g++ src/client.cpp src/socket/socket.cpp src/communicator/communicator.cpp src/gui/window.cpp \
	src/utils/global-controler/global-controler.cpp \
	src/gui/chat/chat-window.cpp \
	src/gui/input/input-window.cpp \
	src/gui/box-window/box-window.cpp \
	src/utils/message/message.cpp \
	-lncurses -pthread -o build/TCP-client
clear:
	rm -r -f build/*
init:
	mkdir build
run-server: server
	./build/TCP-server
run-client: client
	./build/TCP-client