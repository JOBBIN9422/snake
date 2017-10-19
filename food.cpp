#include "food.h"
using namespace std;

Food::Food(int x, int y) : Fl_Box(x, y, 20, 20)
{
	this->box(FL_OFLAT_BOX);
	this->color(FL_RED);
	this->x = x;
	this->y = y;
	this->show();
}

void Food::move(int maxX, int maxY)
{
	this->hide();
	//jump to a random position within bounds (max x/y)
	int newX = (rand() % maxX/20)*20;
	int newY = (rand() % maxY/20)*20;
	this->position(newX, newY);	//move the segment to its new position
	this->x = newX;				//update segment coordinates
	this->y = newY;
	
	this->show();
}

int Food::getX()
{
	return this->x;
}

int Food::getY()
{
	return this->y;
}	
