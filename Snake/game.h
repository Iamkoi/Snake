#pragma once
#include"wall.h"
#include"food.h"
#include"snake.h"
#include<iostream>
#include<windows.h>
#include <conio.h>//����̨�������ͷ�ļ�
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

	int press();//press the key
	void play();//endless loop
	void gameover();//the snake dead
};

GAME::GAME()
{
	food.set_loc();
	rfood.set_loc();

	wall.print_wall();
	food.print_food();
	rfood.print_food();
}

void GAME::handle()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
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
	if (snake.head().x == 0 || snake.head().x == wall.getwidth() - 1 ||snake.head().y == 0 || snake.head().y == wall.getheight() - 1)
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

	if (_kbhit())//����û������˼����е�ĳ����
	{
		fflush(stdin);//��ջ��������ַ�

		//getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224���ڶ��ε��÷��صĲ���ʵ��ֵ
		key = _getch();//��һ�ε��÷��صĲ���ʵ��ֵ
		key = _getch();//�ڶ��ε��÷���ʵ��ֵ
	}

	switch (key)
	{
	case 75:
		dir = 3;//����
		break;
	case 77:
		dir = 1;//����
		break;
	case 72:
		dir = 4;//����
		break;
	case 80:
		dir = 2;//����
		break;
	}

	if (key==0||dir - snake.direction == 2 || dir - snake.direction == -2)//δ�������뵱ǰ�����෴�����յ�ǰ�����н�
		dir = snake.direction;

	return dir;
}

void GAME::play()//endless loop
{
	handle();
	int eat = 0;

	while (true)
	{
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

			eat = 0;
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

			eat = (eat + 1) % 5;
			snake.delete_tail = 0;
			score += rfood.mark;
		}

		snake.direction = press();
		snake.move();
		Sleep(snake.speed);

	}
}

void GAME::gameover()
{
	gotoxy(15, 20);
	cout << "game over";
	gotoxy(0, wall.getheight());
}