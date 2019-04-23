#include "hole.h"
#include "term.h"
#include <iostream>

Hole::Hole()
{

}

Hole::Hole(int _x, int _y)
{
	this->_x = _x;
	this->_y = _y;
	_present = true;
}

void Hole::handleEvent(Event *e)
{

}

void Hole::display()
{
	std::cout << cursorPosition(_x, _y) << '^';
}

void Hole::present(bool _present)
{
	this->_present = _present;
}

bool Hole::present()
{
	return _present;
}

void Hole::x(int _x)
{
	this->_x = _x;
}

void Hole::y(int _y)
{
	this->_y = _y;
}

int Hole::x()
{
	return _x;
}

int Hole::y()
{
	return _y;
}