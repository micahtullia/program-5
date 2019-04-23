#include "level.h"
#include "term.h"
#include "application.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cmath>

Level::Level() : room(0), holes(0), maps(0, std::vector<std::string>(0))
{
	srand(time(NULL));
	_px = _py = 0;
	fileRead();
	parseMap();
}

Level::Level(int _lnum, std::vector<std::vector<std::string>> &_maps)
{
	this->_lnum = _lnum;
	this->maps = _maps;
	parseMap();
}

void Level::fileRead()
{
	std::ifstream file("levels.txt");
	std::vector<std::string> map;

	if(file.is_open())
	{
		std::string line;
		while(getline(file, line))
		{
			if(line.substr(0,2) == "//")
			{
				maps.push_back(map);
				map.clear();
				continue;
			}
			map.push_back(line);
		}
	}
	file.close();
}

void Level::parseMap()
{
	for(int y = 0; y < maps[_lnum].size(); y++)
	{
		for(int i = 0; i < maps[_lnum][y].size(); i++)
		{
			std::string line = maps[_lnum][y];
			if(line[i] == '@')
			{
				player = new Player(i+1, y+1);
			}else if(line[i] == '0')
			{
				Boulder *boulder = new Boulder(i+1, y+1);
				room.push_back(boulder);
			}else if (line[i] == '^')
			{
				Hole *hole = new Hole(i+1, y+1);
				holes.push_back(hole);
			}
		}
	}
}

void Level::handleEvent(Event *e)
{
	bool flag = false, flag2 = false;
	_px = player->x();
	_py = player->y();
	if(e->type() != "keyboard") { return; }
	
	KeyboardEvent *k = (KeyboardEvent *) e;
	switch(k->key())
	{
		case 'h':
			_px--;
			flag = boulderDetection(_px, _py, _px-1, _py);
			break;
		case 'j':
			_py++;
			flag = boulderDetection(_px, _py, _px, _py+1);
			break;
		case 'k':
			_py--;
			flag = boulderDetection(_px, _py, _px, _py-1);
			break;
		case 'l':
			_px++;
			flag = boulderDetection(_px, _py, _px+1, _py);
			break;
		case 'y':
			_px--;
			_py--;
			flag = boulderDetection(_px, _py, _px-1, _py-1);
			break;
		case 'u':
			_px++;
			_py--;
			flag = boulderDetection(_px, _py, _px+1, _py-1);
			break;
		case 'n':
			_px++;
			_py++;
			flag = boulderDetection(_px, _py, _px+1, _py+1);
			break;
		case 'b':
			_px--;
			_py++;
			flag = boulderDetection(_px, _py, _px-1, _py+1);
			break;
		case 'd':
			debug = true;
			break;
		case '<':
			if(maps[_lnum][_py-1][_px-1] == '<')
			{
				bool move = rand() % 2;
				int num = _lnum;

				switch(_lnum)
				{
					case 0:
						num = move ? 2 : 1;
						message = "Welcome to level 2\n";
						break;
					case 1:
					case 2:
						num = move ? 4 : 3;
						message = "Welcome to level 3\n";
						break;
					case 3:
					case 4:
						num = move ? 6 : 5;
						message = "Welcome to level 4\n";
						break;
				}
				Level *level = new Level(num, maps);
				((Application*)parent())->child(level);
			}
			break;
	}
	flag2 = findS<Hole*>(holes, _px, _py);

	if(!detectWall(_px, _py) and !flag and !flag2 and !squeeze(player->x(), player->y(), _px, _py))
	{
		player->x(_px);
		player->y(_py);
	}
	display();
	player->display();
}

bool Level::boulderDetection(int px, int py, int npx, int npy)
{
	Boulder *b;
	if((b = (Boulder*)findS<Boulder*>(room, px, py)) !=0)
	{
		if(((Boulder*)findS<Boulder*>(room, npx, npy)) == 0 and !detectWall(npx, npy))
			moveBoulder(b, npx, npy);
		else
			return true;
	}
	return false;
}

bool Level::squeeze(int px, int py, int nx, int ny)
{
	if(abs(px-nx) == 1 and abs(py-ny) == 1)
	{
		if((((Boulder*)findS<Boulder*>(room, px, py+1)) and detectWall(px+1, py))
				and (((Boulder*)findS<Boulder*>(room, nx-1, ny)) and detectWall(nx, ny-1)))
			return true;
		if((((Boulder*)findS<Boulder*>(room, px, py-1)) and detectWall(px+1, py))
				and (((Boulder*)findS<Boulder*>(room, nx-1, ny)) and detectWall(nx, ny+1)))
			return true;
		if((((Boulder*)findS<Boulder*>(room, px+1, py)) and detectWall(px, py-1))
				and (((Boulder*)findS<Boulder*>(room, nx, ny+1)) and detectWall(nx-1, ny)))
			return true;
		/*if((((Boulder*)findS<Boulder*>(room, px, py+1)) and detectWall(px+1, py))
				and (((Boulder*)findS<Boulder*>(room, nx-1, ny)) and detectWall(nx, ny-1)))
			return true;*/
	}
	return false;
}

bool Level::detectWall(int _x, int _y)
{
	return (maps[_lnum][_y-1][_x-1] == '-' or maps[_lnum][_y-1][_x-1] == '|');
}

int Level::numBoulders()
{
	int sum = 0;
	for(int i = 0; i < room.size(); i++)
		sum+=room[i]->present();
	return sum;
}

void Level::moveBoulder(Boulder *b, int x, int y)
{
	Hole *hole;
	b->x(x);
	b->y(y);
	if((hole = (Hole*)findS<Hole*>(holes, x, y)) != 0)
	{
		hole->present(false);
		b->present(false);
	}
	if(_lnum > 4 && numBoulders() == 0)
	{
		gameVictory();
	}
}

template<typename T> 
T Level::findS(std::vector<T> v, int x, int y)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i]->x() == x and v[i]->y() == y and v[i]->present())
			return v[i];
	}
	return 0;
}

void Level::display()
{
	std::cout << clearScreen << cursorPosition(1, 1);

	for(int j = 0; j < maps[_lnum].size(); j++)
	{
		for(int i = 0; i < maps[_lnum][j].size(); i++)
		{
			if(maps[_lnum][j][i] != '@' and maps[_lnum][j][i] != '0' and maps[_lnum][j][i] != '^')
			{
				std::cout << maps[_lnum][j][i];
			}else
			{
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
	std::cout.flush();
	
	for(int i = 0; i < room.size(); i++)
	{
		if(room[i]->present())
			room[i]->display();
	}
	for(int i = 0; i < holes.size(); i++)
	{
		if(holes[i]->present())
			holes[i]->display();
	}
	player->display();
}

void Level::gameVictory()
{
	
}