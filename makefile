all: game

game: game.o segment.o snake.o food.o 
	g++ -std=c++11 -lfltk -lfltk_images segment.o main.o snake.o food.o -o game
	
game.o: main.cpp snake.h food.h
	g++ -std=c++11 -c -lfltk -lfltk_images main.cpp
	
segment.o: segment.cpp segment.h
	g++ -std=c++11 -c -lfltk -lfltk_images segment.cpp
	
snake.o: snake.cpp snake.h segment.h food.h
	g++ -std=c++11 -c -lfltk -lfltk_images snake.cpp
	
food.o: food.cpp food.h
	g++ -std=c++11 -c -lfltk -lfltk_images food.cpp
clean:
	rm *.o game
	
