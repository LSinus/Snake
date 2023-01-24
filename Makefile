all: compile link clean run

compile:
	g++ -Isrc/include -c src/include/dependencies/scoreboard.cpp
	g++ -Isrc/include -c src/include/dependencies/size.cpp
	g++ -Isrc/include -c src/include/dependencies/utility.cpp
	g++ -Isrc/include -c src/include/dependencies/apple.cpp
	g++ -Isrc/include -c src/include/dependencies/snake.cpp
	g++ -Isrc/include -c src/include/dependencies/rendering.cpp
	g++ -Isrc/include -c main.cpp

link:
	g++ main.o apple.o utility.o scoreboard.o size.o rendering.o snake.o -o Snake -Wl,-rpath=/bin -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del main.o rendering.o utility.o apple.o snake.o size.o scoreboard.o

run:
	Snake