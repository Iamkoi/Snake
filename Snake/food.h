#ifndef FOOD_H
#define FOOD_H

#include<iostream>
#include<windows.h>
#include<ctime>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"game.h"
using namespace std;

extern void gotoxy(int x, int y);
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


/*FOOD*/
void FOOD::set_loc()
{
	WALL wall;
	srand(time(NULL));
	food_x = rand() % (wall.getwidth() - 2) + 1;
	food_y = rand() % (wall.getheight() - 2) + 1;
}
void FOOD::print_food()
{
	//blue
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_BLUE);
	gotoxy(food_x, food_y);
	cout << "*";
	//set back to white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void FOOD::delete_food()
{
	gotoxy(food_x, food_y);
	cout << "  ";
}

/*RANDOM_FOOD*/
void RANDOM_FOOD::set_loc()
{
	WALL wall;
	srand(time(NULL));
	rfood_x = rand() % (wall.getwidth() - 2) + 1;
	rfood_y = rand() % (wall.getheight() - 2) + 1;
}
void RANDOM_FOOD::print_food()
{
	if (ifexist == 1)//存在随机食物
	{
		//Magenta
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_BLUE);
		gotoxy(rfood_x, rfood_y);
		cout << "$";
		//set back to white
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}
void RANDOM_FOOD::delete_food()
{
	gotoxy(rfood_x, rfood_y);
	cout << "  ";
}

#endif