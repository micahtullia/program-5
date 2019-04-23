//Implementation of the application class
// $Revision: 1.4 $
//    $Log: application.cpp,v $
//    Revision 1.4  2017/02/13 13:42:22  1ea49c2b19284e86b645075d033e28d0
//    Turned the cursor off and created initial display.
//
//    Revision 1.3  2017/02/13 03:22:19  1ea49c2b19284e86b645075d033e28d0
//    Fixed a silly little typo.
//
//    Revision 1.2  2017/02/13 03:12:25  1ea49c2b19284e86b645075d033e28d0
//    Autoparent the child.
//
//    Revision 1.1  2017/02/13 02:25:29  pngwen
//    Initial revision
//
#include <string>
#include <unistd.h>
#include <iostream>
#include "application.h"
#include "term.h"

Application::Application()
{
   int w,h;  //width and height

   //get the size
   getTermSize(w,h);

   //set position and size
   x(1);
   y(1);
   width(w);
   height(h);

   //start childless and asleep
   running(false);
   child(nullptr);
}


//event handling
void 
Application::handleEvent(Event *e)
{
    //pass the event to our child (if we have one)
    if(child()) {
        child()->handleEvent(e);
    }
}


//drawing functions
void 
Application::display()
{
    //we will assume that we want the cursor off
    std::cout << cursorOff;

    //display the child, if there is one
    if(child()) {
        child()->display();
    }
}
  

//retrievrand dispatch events until the applicstion is no longer
//running.
void 
Application::eventLoop()
{
    int w;
    int h;

    //initialize to the running state
    running(true);

    //we assume cbreak mode, also clear the screen and do our display
    kin.cbreakMode();
    clear();
    display();

    //run until told to stop.  Poll for events at a rate of
    //once per milisecond
    while(running()) 
    {
        //check for a keyboard event
        if(kin.hasInput()) {
            //post a keyboard event
            Event *e = new KeyboardEvent(kin.getKey());
            if(child()) {
                child()->handleEvent(e);
            }
            delete e;
        }

        //check for a resize event
        getTermSize(w, h);
        if(w != width() or h != height()) {
            //set my new width and height
            this->width(w);
            this->height(h);

            //post a resize event
            Event *e = new ResizeEvent(w, h);
            if(child()) {
                child()->handleEvent(e);
            }
            delete e;
        }
        usleep(1000);
    }
}


//field functuons
Widget *
Application::child()
{
    return _child;
}


void 
Application::child(Widget *_child)
{
    this->_child = _child;

    // add a parent to the child 
    if(this->child()) {
        this->child()->parent(this);
    }
}


bool 
Application::running()
{
    return _running;
}


void 
Application::running(bool _running)
{
    this->_running = _running;
}


KeyboardEvent::KeyboardEvent(keycode kc)
{
    this->_key = kc;
    if(kc > 0x1f and kc <= 0xff) {
        this->_printable = (char) kc;
    } else {
        this->_printable = 0x00;
    }
}


std::string 
KeyboardEvent::type()
{
    return "keyboard";
}


keycode 
KeyboardEvent::key()
{
    return this->_key;
}


char 
KeyboardEvent::printable()
{
    return this->_printable;
}

ResizeEvent::ResizeEvent(int w, int h)
{
    this->_width = w;
    this->_height = h;
}


std::string 
ResizeEvent::type()
{
    return "resize";
}


int 
ResizeEvent::width()
{
    return this->_width;
}


int 
ResizeEvent::height()
{
    return this->_height;
}


