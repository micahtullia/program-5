#include "boulder.h"
#include "term.h"
#include <iostream>

Boulder::Boulder()
{

}

Boulder::Boulder(int _x, int _y)
{
	this->_x = _x;
	this->_y = _y;
	_present = true;
}

void Boulder::handleEvent(Event *e)
{

}

void Boulder::display()
{
	std::cout << cursorPosition(_x, _y) << reverseVideo;
	std::cout << _shape << normal;
}

void Boulder::present(bool _present)
{
	this->_present = _present;
}

bool Boulder::present()
{
	return _present;
}

void Boulder::shape(char _shape)
{
	this->_shape = _shape;
}

char Boulder::shape()
{
	return _shape;
}

void Boulder::x(int _x)
{
	this->_x = _x;
}

void Boulder::y(int _y)
{
	this->_y = _y;
}

int Boulder::x()
{
	return _x;
}

int Boulder::y()
{
	return _y;
}