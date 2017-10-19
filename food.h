#pragma once 
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>

class Food : public Fl_Box
{
	private:
		int x, y;	//food coordinates in the game window
	
	public:
		Food(int x, int y);
		
		//jump to a random position within bounds specified by max x/y
		void move(int maxX, int maxY);
		int getX();
		int getY();
};
