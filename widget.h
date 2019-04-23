// This is an abstraction of display elements used in terminal programs.
// By itself, it does nothing as it contains one pure virtual function.
// Revision: $Revision: 1.3 $
// Change Log
//   $Log: widget.h,v $
//   Revision 1.3  2017/02/13 02:27:42  pngwen
//   Just a little cleanup of names and such.
//
//   Revision 1.2  2017/02/12 18:13:43  root
//   Cleaned up a couple of compile errors.
//   Added parentage support.
//
//   Revision 1.1  2016/03/17 16:03:33  pngwen
//   Initial revision
//
#ifndef WIDGET_H
#define WIDGET_H
#include "event.h"

class Widget {

public:
  Widget(int _x, int _y, int _width, int _height);
  Widget();

  //event handling
  virtual void handleEvent(Event *e)=0;

  //drawing functions
  virtual void display()=0;
  virtual void clear();

  //set our parameters
  virtual int x();
  virtual void x(int _x);
  virtual int y();
  virtual void y(int _y);
  virtual int width();
  virtual void width(int _width);
  virtual int height();
  virtual void height(int _height);
  virtual Widget *parent();
  virtual void parent(Widget *_parent);

 protected:
    int _x;
    int _y;
    int _width;
    int _height;
    Widget *_parent;
};

#endif // Widget_h
