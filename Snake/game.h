#ifndef GAME_H
#define GAME_H

#include"wall.h"
#include"food.h"
#include"snake.h"
#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
#include <conio.h>//控制台输入输出头文件

#pragma comment(lib, "Winmm.lib")//play_sound

#define textname1 "simple.txt"
#define textname2 "medium.txt"
#define textname3 "difficult.txt"

using namespace std;

class GAME
{
private:
	int score = 0;
	string name;
	string level;
	struct Node
	{
		string myname;
		int myscore = 0;
	};
public:
	WALL wall;
	FOOD food;
	RANDOM_FOOD rfood;
	SNAKE snake;

	GAME();
	void hide_cursor();

	bool check_wall();//if meet the wall
	bool check_food();//if meet the food
	bool check_rfood();//if meet the rfood

	void first_page();//choose the module
	void choose_module();

	void input_name();

	int press();//press the key
	void play();//endless loop
	void printgameover(int x, int y);//GAME OVER!
	void printstatus();//print your status
	void printscore(bool update);//update the score
	ifstream& open_file(ifstream &in, const string &file);
	void printhistory();
	void gameover();//the snake dead
};

#endif