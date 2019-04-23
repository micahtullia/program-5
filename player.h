#ifndef PLAYER_H
#define PLAYER_H
#include "widget.h"

class Player : public Widget
{
public:
    Player();
    Player(int, int);

    //widget functions
    virtual void handleEvent(Event *);
    virtual void display();

	virtual void shape(char);
	virtual char shape();
	
	virtual int ix();
	virtual int iy();
	virtual int x();
	virtual int y();
	virtual int z();
	
	virtual void x(int);
	virtual void y(int);
	virtual void z(int);

private:
	char _shape='@';
	int _x;
	int _y;
	int _z;
	int _ix;
	int _iy;
};

#endif