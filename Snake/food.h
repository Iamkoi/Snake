#ifndef FOOD_H
#define FOOD_H

#include<iostream>
#include<windows.h>
#include<ctime>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include"game.h"
using namespace std;


class FOOD
{
private:
public:
	int food_x;
	int food_y;
	int mark = 1;
	void set_loc();
	void print_food();
	void delete_food();
};

class RANDOM_FOOD
{
private:
public:
	int rfood_x;
	int rfood_y;
	int mark = 5;
	bool ifexist = 0;
	int step = 0;//食物出现后已经走了多少步
	void set_loc();
	void print_food();
	void delete_food();
};

#endif