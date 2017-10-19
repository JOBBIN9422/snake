#pragma once 
#include "segment.h"
#include <vector>
#include <FL/Fl_Double_Window.H>
#include <queue>


class Snake : public Fl_Double_Window
{
	private:
		std::vector<Segment*> body;     //snake segments (change this to a queue?)
		std::queue<std::string> buffer; //input buffer 
		
		int startX, startY;			//starting position
		int size;					//number of segments in the snake 
		bool dead;					//Triggered on collision with self/walls
		bool input; 
		std::string direction;		//The snake's current heading (change to enum?)

	public:
		Snake(int numSegments, int x, int y); //constructor
		int handle(int event);				  //FLTK event handler
		int getSize();					
		
		bool checkDead();					  //return game state

		void move();						  //Step the snake in the current direction
		void addSegment();
		void bufferInput();
		void checkCollision(); /*check if the snake has:
								 hit itself
								 hit a boundary
								 hit the food*/
};
