#include "player.h"
#include "term.h"
#include "application.h"
#include <iostream>

Player::Player()
{
	_x = _y = _ix = _iy = _z = 0;
}

Player::Player(int _x, int _y)
{
	this->_x = _x;
	this->_y = _y;
	this->_ix = _x;
	this->_iy = _y;
}

void Player::handleEvent(Event *e)
{    

}

void Player::display()
{
	std::cout << cursorPosition(_x, _y) << _shape;
	std::cout.flush();
}


void Player::shape(char _shape)
{
	this->_shape = _shape;
}

char Player::shape()
{
	return _shape;
}

int Player::ix()
{
	return _ix;
}

int Player::iy()
{
	return _iy;
}

int Player::x()
{
	return _x;
}

int Player::y()
{
	return _y;
}

int Player::z()
{
	return _z;
}

void Player::x(int _x)
{
	this->_x = _x;
}

void Player::y(int _y)
{
	this->_y = _y;
}

void Player::z(int _z)
{
	this->_z = _z;
}
