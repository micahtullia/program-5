// Functions for the widget class.
// Revision: $Revision: 1.2 $
// Change Log
//   $Log: widget.cpp,v $
//   Revision 1.2  2017/02/12 18:14:37  root
//   Added parentage support.
//
//   Revision 1.1  2016/03/17 16:02:36  pngwen
//   Initial revision
//

#include "widget.h"
#include "termmanip.h"
#include <iostream>

using namespace std;

Widget::Widget(int _x, int _y, int _width, int _height)
{
  this->_x = _x;
  this->_y = _y;
  this->_width = _width;
  this->_height = _height;
  this->_parent = nullptr;
}


Widget::Widget()
{
  this->_x = 0;
  this->_y = 0;
  this->_width = 0;
  this->_height = 0;
  this->_parent = nullptr;
}


void
Widget::clear()
{
  //paint over the widget
  for(int i=0; i<_height; i++) {
    cout << cursorPosition(_x, _y+i);
    for(int j=0; j<_width; j++) {
      cout << ' ';
    }
  }

  cout.flush();
}

int
Widget::x()
{
  return _x;
}


void
Widget::x(int _x)
{
  this->_x = _x;
}


int
Widget::y()
{
  return _y;
}


void
Widget::y(int _y)
{
  this->_y = _y;
}


int
Widget::width()
{
  return _width;
}


void
Widget::width(int _width)
{
  this->_width = _width;
}


int
Widget::height()
{
  return _height;
}


void
Widget::height(int _height)
{
  this->_height = _height;
}



Widget *
Widget::parent()
{
  return this->_parent;
}


void 
Widget::parent(Widget *_parent)
{
  this->_parent = _parent;
}

