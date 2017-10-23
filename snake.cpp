#include "snake.h"
#include "food.h"
using namespace std;

Snake::Snake(int numSegments, int x, int y) : startX(x), startY(y), maxBufferSize(3), 
Fl_Double_Window(800, 600, "shitty snake game"), direction("LEFT"), dead(false)
{
	this->color(FL_BLACK);
	srand(time(NULL));
	for (int i = 0; i < numSegments; i++)
	{
		Segment* bodySeg = new Segment(x + (20*i), y);
		body.push_back(bodySeg);
	}
	
	food = new Food(0, 0);
	food->move(this->w(), this->h()); //randomize initial food position
	this->show();
}

bool Snake::checkDead()
{
	return this->dead;
}

void Snake::addSegment()
{
	//get tail pos
	int tailX = body.back()->getX();
	int tailY = body.back()->getY();
	
	Segment* newSeg = new Segment(tailX, tailY);
	this->add(newSeg);	//add the segment as a child of the window so it is drawn
	body.push_back(newSeg);
	return;
}

void Snake::checkCollision()
{
	int headX = body.front()->getX();
	int headY = body.front()->getY();
	int foodX = food->getX();
	int foodY = food->getY();
	//check for snake eating itself
	for(int i = 1; i < body.size(); i++) //start loop at 1 so we exclude the head!
	{	
		if(body.at(i)->getX() == headX && body.at(i)->getY() == headY)
		{
			//cout << "hit snake" << endl;
			this->dead = true;
		}
	}
	if(headX == foodX && headY == foodY)
	{	//check for food collision
		//cout << "hit food" << endl;
		food->move(this->w(), this->h());
		this->addSegment();
	}
	
	//check for out of bounds
	if(headX >= this->w() || headX < 0 || headY >= this->h() || headY < 0)
	{
		this->dead = true;
	}
}

void Snake::move()
{
	if (!buffer.empty())
	{	//read direction from the input buffer
		this->direction = buffer.front();
		buffer.pop();
	}
	
	Segment* moveMe = body.back(); //select the segment at the end of the vector
	body.pop_back();			   
	
	//get head pos
	int headX = body.front()->getX();
	int headY = body.front()->getY();
	//move head based on current direction
	if(this->direction == "UP")
		moveMe->move(headX, headY - 20);
	else if(this->direction == "DOWN")
		moveMe->move(headX, headY + 20);
	else if(this->direction == "LEFT")
		moveMe->move(headX - 20, headY);
	else
		moveMe->move(headX + 20, headY);
	//insert the last tail segment as the new head	
	body.insert(body.begin(), moveMe);
	return;
}

int Snake::getSize() { return body.size(); }

int Snake::handle(int event)
{
	switch(event)
	{
		case FL_KEYDOWN:
			
			if(Fl::event_key() == FL_Up)
			{	//note that the snake cannot reverse directions (eat itself)
				if(this->direction != "DOWN" && buffer.size() < maxBufferSize)
				{
					buffer.push("UP"); //add player input to input buffer
				}
				return 1;
			}
			else if(Fl::event_key() == FL_Down)
			{
				if(this->direction != "UP" && buffer.size() < maxBufferSize)
				{
					buffer.push("DOWN");
				}
				return 1;				
			}
			else if(Fl::event_key() == FL_Left)
			{
				if(this->direction != "RIGHT" && buffer.size() < maxBufferSize)
				{
					buffer.push("LEFT");
				}
				return 1;
			}
			else if(Fl::event_key() == FL_Right)
			{
				if(this->direction != "LEFT" && buffer.size() < maxBufferSize)
				{
					buffer.push("RIGHT");
				}
				return 1;
			}
		default: return Fl_Widget::handle(event);
	}
}
