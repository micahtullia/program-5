#ifndef HOLE_H
#define HOLE_H
#include "widget.h"

class Hole : public Widget
{
public:
    Hole();
    Hole(int _x, int _y);

    //widget functions
    virtual void handleEvent(Event *e);
    virtual void display();

    virtual void present(bool _present);
    virtual bool present();

	virtual void x(int _x);
	virtual void y(int _y);
	virtual int x();
	virtual int y();
private:
    bool _present;
	int _x;
	int _y;
};

#endif