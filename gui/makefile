all: build run

build: gui.cpp main.cpp 
	@g++ -g gui.cpp main.cpp -o main -lncurses -ltinfo

run:
	@./main	

clean:
	@rm main