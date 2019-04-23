#ifndef LEVEL_H
#define LEVEL_H
#include "widget.h"
#include "player.h"
#include "boulder.h"
#include "hole.h"
#include <vector>
#include <string>

class Level : public Widget
{
public:
    Level();
    Level(int, std::vector<std::vector<std::string>>&);

    //widget functions
    virtual void handleEvent(Event*);
    virtual void display();
	
	virtual bool detectWall(int, int);
	virtual void moveBoulder(Boulder*, int, int);
	template<typename T> T findS(std::vector<T>, int, int);
	virtual bool boulderDetection(int, int, int, int);
	virtual int numBoulders();
	virtual bool squeeze(int, int, int, int);
	
	virtual void fileRead();
	virtual void parseMap();
	virtual void gameVictory();

private:
	int _lnum;
	int _px;
	int _py;
	bool debug;
	Player *player;
	std::string message;
	std::vector<Boulder*> room;
	std::vector<Hole*> holes;
	std::vector<std::vector<std::string>> maps;
};

#endif