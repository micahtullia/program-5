#ifndef BOULDER_H
#define BOULDER_H
#include "widget.h"

class Boulder : public Widget
{
public:
    Boulder();
    Boulder(int _x, int _y);

    //widget functions
    virtual void handleEvent(Event *e);
    virtual void display();

    virtual void present(bool _present);
    virtual bool present();

	virtual void shape(char _shape);
	virtual char shape();

	virtual void x(int _x);
	virtual void y(int _y);
	virtual int x();
	virtual int y();
private:
    bool _present;
	char _shape='0';
	int _x;
	int _y;
};

#endif