#ifndef WALL_H
#define WALL_H
//#include"game.h"
#include<windows.h>
#include<iostream>
using namespace std;

class WALL
{
private:
	int height = 25;
	int width = 80;
public:
	void print_wall();
	int getwidth() const;
	int getheight() const;
};


#endif
