#pragma once
#include"wall.h"
#include"food.h"
#include"snake.h"
#include<iostream>
#include<windows.h>
#include <conio.h>//控制台输入输出头文件
using namespace std;

class GAME
{
private:
	int score = 0;
public:
	WALL wall;
	FOOD food;
	RANDOM_FOOD rfood;
	SNAKE snake;

	GAME();
	void handle();

	bool check_wall();//if meet the wall
	bool check_food();//if meet the food
	bool check_rfood();//if meet the rfood

	void first_page();//choose the module
	void choose_module();

	int press();//press the key
	void play();//endless loop
	void printgameover(int x, int y);//GAME OVER!
	void gameover();//the snake dead
};

void GAME::first_page()//choose the module
{
	cout << "\t \t\t" << "Snake\t\t" << "\t\t" << endl;
	cout << "\t\t\t\t——welcome\t\t" << endl;
	cout << "\t=========================================" << endl;
	cout << "\t&\t\t" << "1.simple\t\t" << "&\t" << endl;
	cout << "\t&\t\t" << "2.midulm\t\t" << "&\t" << endl;
	cout << "\t&\t\t" << "3.difficult\t\t" << "&\t" << endl;
	cout << "\t=========================================" << endl;
	cout << "\t1. Press the key to choose the module." << endl;
	cout<<"\t2. Press 'Enter' to start the game." << endl;
}

void GAME::choose_module()
{
	system("CLS");
	gotoxy(0, 0);
	first_page();

	int module_num;
	cin >> module_num;
	switch (module_num)
	{
	case 1:snake.speed = 200; break;
	case 2:snake.speed = 100; break;
	case 3:snake.speed = 50; break;
	default:cout << "Input Error,please input it correctly."; system("pause"); choose_module(); break;
	}
}

GAME::GAME()
{
	food.set_loc();
	rfood.set_loc();

	choose_module();
	system("CLS");

	wall.print_wall();
	food.print_food();
	rfood.print_food();
}

void GAME::handle()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

void gotoxy(int x, int y)//move the cursor to (x,y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool GAME::check_wall()//if meet the wall
{
	bool ret = 0;
	WALL wall;
	if (snake.head().x <= 1 || snake.head().x >= wall.getwidth() - 2 ||snake.head().y <= 1 || snake.head().y >= wall.getheight() - 2)
		ret = 1;
	return ret;
}

bool GAME::check_food()//if meet the food
{
	bool ret = 0;
	if (snake.head().x == food.food_x&&snake.head().y == food.food_y)
		ret = 1;
	return ret;
}

bool GAME::check_rfood()//if meet the random food
{
	bool ret = 0;
	if (rfood.ifexist&&snake.head().x == rfood.rfood_x&&snake.head().y == rfood.rfood_y)
		ret = 1;
	return ret;
}

int GAME::press()
{
	int key = 0;
	int dir = 0;

	if (_kbhit())//如果用户按下了键盘中的某个键
	{
		fflush(stdin);//清空缓冲区的字符

		//getch()读取方向键的时候，会返回两次，第一次调用返回0或者224，第二次调用返回的才是实际值
		key = _getch();//第一次调用返回的不是实际值
		key = _getch();//第二次调用返回实际值
	}

	switch (key)
	{
	case 75:
		dir = 3;//往左
		break;
	case 77:
		dir = 1;//往右
		break;
	case 72:
		dir = 4;//往上
		break;
	case 80:
		dir = 2;//往下
		break;
	}

	if (key==0||dir - snake.direction == 2 || dir - snake.direction == -2)//未按键或与当前方向相反，按照当前方向行进
		dir = snake.direction;

	return dir;
}

void GAME::play()//endless loop
{
	handle();
	int eat = -1;

	while (true)
	{
		if (rfood.ifexist == true)
			rfood.step++;
		if (rfood.step >= 30)
		{
			rfood.delete_food();
			rfood.step = 0;
			rfood.ifexist = false;
		}

		snake.delete_tail = 1;
		if (eat == 4)//create random food
		{
			rfood.ifexist = 1;//exist

			//location
			rfood.set_loc();
			while(rfood.rfood_x==food.food_x&&rfood.rfood_y == food.food_y)
				rfood.set_loc();

			//print
			rfood.print_food();	

			eat = -1;
		}

		if (check_wall())//meet the wall;
		{
			gameover();
			break;
		}

		else if (check_food())//meet the food
		{
			eat = (eat + 1) % 5;
			snake.delete_tail = 0;
			score += food.mark;

			food.set_loc();
			food.print_food();
		}

		else if(check_rfood())//meet the rfood
		{
			rfood.ifexist = 0;//not exist
			//rfood.delete_food();

			//eat = (eat + 1) % 5;
			snake.delete_tail = 0;
			score += rfood.mark;
		}

		snake.direction = press();
		snake.move();

		if (snake.direction % 2 == 1)
			Sleep(snake.speed);
		else
			Sleep(2*snake.speed);

	}
}

void GAME::printgameover (int x,int y)
{
	gotoxy(x, y);
	cout <<" #####     #    #     # #######    ####### #     # ####### ######     ###";
	gotoxy(x, y + 1);
	cout << "#     #   # #   ##   ## #          #     # #     # #       #     #    ###";
	gotoxy(x, y + 2);
	cout << "#        #   #  # # # # #          #     # #     # #       #     #    ###";
	gotoxy(x, y + 3);
	cout << "#  #### #     # #  #  # #####      #     # #     # #####   ######      # ";
	gotoxy(x, y + 4);
	cout << "#     # ####### #     # #          #     #  #   #  #       #   #        ";
	gotoxy(x, y + 5);
	cout << "#     # #     # #     # #          #     #   # #   #       #    #     ###";
	gotoxy(x, y + 6);
	cout << " #####  #     # #     # #######    #######    #    ####### #     #    ###";
}

void GAME::gameover()
{
	int x = 3, y = 8;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow

	printgameover(x, y);
	gotoxy(wall.getwidth() / 2 - 7, y + 9);
	cout << "SCORE: " << score;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//white

	gotoxy(0, wall.getheight());
}