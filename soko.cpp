#include "application.h"
#include "level.h"
#include "term.h"
#include <iostream>

int main()
{
	Application *sokoban = new Application();
	Level *level = new Level();
	
	sokoban->child(level);
	std::cout << cursorOff;
	std::cout.flush();
	
	sokoban->eventLoop();
    
	std::cout << cursorOn << normal << clearScreen << '\n';
	
	return 0;
}