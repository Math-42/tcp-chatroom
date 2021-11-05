all: build run

build: gui.cpp 
	@g++ -g gui.cpp -o gui -lncurses -ltinfo

run:
	@./gui	

clean:
	@rm gui