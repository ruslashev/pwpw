src = main.cc
bin = pwpw
cflags = -g -std=c++17

all:
	g++ $(src) -o $(bin)
	./$(bin)

