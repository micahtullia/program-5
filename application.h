// This is a widget derivative which implements an application.
// An application widget is meant to act as the root widget for
// a program.  It doesnot draw anything itself, but rather handles
// that by drawing its child widget.
// The application widget is also responsible for gathering and
// dispatching keyboard and resize events.  It responds to these
// events by creating and passing event objects to its child 
// widget.
//
// $Revision: 1.1 $
//   $Log: application.h,v $
//   Revision 1.1  2017/02/13 02:25:29  pngwen
//   Initial revision
//
#ifndef APPLICATION_H
#define APPLICATION_H
#include "widget.h"
#include "keystream.h"

class Application : public Widget
{
public:
  Application();

  //event handling
  virtual void handleEvent(Event *e);

  //drawing functions
  virtual void display();
  
  //retrievrand dispatch events until the applicstion is no longer
  //running.
  virtual void eventLoop();

  //field functuons
  virtual Widget *child();
  virtual void child(Widget *_child);
  virtual bool running();
  virtual void running(bool _running);

protected:
  //we can have one child as an application
  Widget *_child;

  //true if the applicatiob is running
  bool _running;
};


//application events
class KeyboardEvent : public Event
{
public:
    KeyboardEvent(keycode kc);
    virtual std::string type();
    virtual keycode key();
    virtual char printable();

protected:
    keycode _key;
    char _printable;
};


class ResizeEvent : public Event
{
public:
    ResizeEvent(int w, int h);
    virtual std::string type();
    virtual int width();
    virtual int height();

protected:
    int _width;
    int _height;
};
#endif
