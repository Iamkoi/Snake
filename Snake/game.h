#pragma once
#include"wall.h"
#include"food.h"
#include"snake.h"
#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
#include <conio.h>//����̨�������ͷ�ļ�

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

void GAME::first_page()//choose the module
{
	cout << "\t \t\t" << "Snake\t\t" << "\t\t" << endl;
	cout << "\t\t\t\t����welcome\t\t" << endl;
	cout << "\t=========================================" << endl;
	cout << "\t&\t\t" << "1.simple\t\t" << "&\t" << endl;
	cout << "\t&\t\t" << "2.medium\t\t" << "&\t" << endl;
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
	case 1:snake.speed = 200; level = "simple"; break;
	case 2:snake.speed = 100; level = "medium"; break;
	case 3:snake.speed = 50;  level = "difficult"; break;
	default:cout << "Input Error,please input it correctly."; system("pause"); choose_module(); break;
	}
}

void GAME::input_name()
{
	system("CLS");
	gotoxy(0, 0);
	cout << "Please input your name: ";
	cin >> name;
}

GAME::GAME()
{
	food.set_loc();
	rfood.set_loc();

	choose_module();
	system("CLS");

	input_name();
	system("CLS");

	snake.initial_snake();
	wall.print_wall();
	food.print_food();
	rfood.print_food();
}

void GAME::hide_cursor()
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
	if (snake.head().x <= 1 || snake.head().x >= wall.getwidth() - 2 ||snake.head().y < 1 || snake.head().y >= wall.getheight() - 1)
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

int GAME::press()//���ص�ǰ�����ļ��ķ���0��ʾû�а���
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
	return dir;
}

void GAME::printstatus()//print your status
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//��ɫ
	gotoxy(wall.getwidth() + 2, 2);
	cout << "# STATUS #";
	gotoxy(wall.getwidth() + 2, 10);
	cout << "====================================";
	gotoxy(wall.getwidth() + 2, 12);
	cout << "# NOTES #";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow
	gotoxy(wall.getwidth() + 2, 4);
	cout << "Name: " << name;
	gotoxy(wall.getwidth() + 2, 6);
	cout << "Score: " << score;
	gotoxy(wall.getwidth() + 2, 8);
	cout << "Module: " << level;

	gotoxy(wall.getwidth() + 2, 14);
	cout << "1. 1 * = 1 score";
	gotoxy(wall.getwidth() + 2, 16);
	cout << "2. 1 $ = 5 scores";
	gotoxy(wall.getwidth() + 2, 20);
	cout << "4. '$' will disappear after 50 steps.";


	gotoxy(wall.getwidth() + 7, 22);
	cout << "��";
	gotoxy(wall.getwidth() + 4, 23);
	cout << "��   ��";
	gotoxy(wall.getwidth() + 7, 24);
	cout << "��";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED);//red
	gotoxy(wall.getwidth() + 2, 18);
	cout << "3. You can press long to accelerate.";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow

}

void GAME::printscore(bool update)//update the score
{
	if (update)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow
		gotoxy(wall.getwidth() + 9, 6);
		cout << score;

	}
}

void GAME::play()//endless loop
{
	hide_cursor();
	printstatus();
	int eat = -1;
	bool update_score = false;

	while (true)
	{
		printscore(update_score);
		update_score = false;

		if (rfood.ifexist == true)
			rfood.step++;
		if (rfood.step >= 50)
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
			while(rfood.rfood_x==food.food_x&&rfood.rfood_y == food.food_y)//rfood��food������ͬһ���ط�
				rfood.set_loc();

			//print
			rfood.print_food();	

			eat = -1;
		}

		if (check_wall())//meet the wall;
		{
			if(snake.head().x==1)
				gotoxy(snake.head().x-1, snake.head().y);
			else
				gotoxy(snake.head().x,snake.head().y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//��ɫ
			cout << "��";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			gameover();
			break;
		}

		else if (check_food())//meet the food
		{
			PlaySound(TEXT("eat_food.wav"), NULL, SND_FILENAME | SND_ASYNC);

			eat = (eat + 1) % 5;
			snake.delete_tail = 0;
			score += food.mark;
			update_score = true;

			food.set_loc();
			food.print_food();
		}

		else if(check_rfood())//meet the rfood
		{
			PlaySound(TEXT("eat_food.wav"), NULL, SND_FILENAME | SND_ASYNC);
			rfood.ifexist = 0;//not exist
			update_score = true;

			//eat = (eat + 1) % 5;
			snake.delete_tail = 0;
			score += rfood.mark;
			rfood.step = 0;
		}

		//�����Ƿ�����Լ����������ƶ��ٶȺͷ���
		int now_dir = press();
		int myspeed;

		if (now_dir == 0 || now_dir - snake.direction == 2 || now_dir - snake.direction == -2)//δ�������뵱ǰ�����෴�����յ�ǰ����ǰ�ٶ��н�
			myspeed = snake.speed;

		else if (now_dir == snake.direction)//����
			myspeed = snake.speed / 8;

		else//����
		{
			myspeed = snake.speed;
			snake.direction = now_dir;
		}

		snake.move();

		if (snake.direction % 2 == 1)
			Sleep(myspeed);
		else
			Sleep(2 * myspeed);
	}
}

void GAME::printgameover (int x,int y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//yellow
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

ifstream& GAME::open_file(ifstream &in, const string &file)
{
	in.close();
	in.clear();
	in.open(file.c_str());
	return in;
}

void GAME::printhistory()
{
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//��ɫ
	cout << "# TOP 10 players #" << endl;
	cout << "# Module: " << level << " #" << endl << endl;
	cout << "name\tscore" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//white

	//read
	ifstream myfile;
	if (level == "simple")
		open_file(myfile, textname1);
	else if (level == "medium")
		open_file(myfile, textname2);
	else 
		open_file(myfile, textname3);

	string readline;
	vector<Node> history;

	Node me;
	me.myname = name;
	me.myscore = score;
	bool ifinsert = false;

	while (!myfile.eof())
	{
		getline(myfile, readline);
		Node tempnode;
		if (readline == "")
			break;

		//���name��score
		int j;
		for (j = 0; j < readline.length() && readline[j] != ' '; j++);
		tempnode.myname=readline.substr(0, j);
		string tscore = readline.substr(j + 1, readline.length() - j);
		tempnode.myscore = atoi(tscore.c_str());

		//�Ƿ����
		if (tempnode.myscore <= score)//����˴εĳɼ�
		{
			ifinsert = true;
			history.push_back(me);
		}

		if (history.size() < 9)
			history.push_back(tempnode);
		else if (history.size() == 9)
		{
			history.push_back(tempnode);
			break;
		}
		else break;
	}
	if (history.size() < 10 && !ifinsert)
		history.push_back(me);

	myfile.close();

	//���
	string textname;
	if (level == "simple")	textname = textname1;
	else if (level == "medium")	textname = textname2;
	else  textname = textname3;
	ofstream outfile(textname);

	for (int k = 0; k < history.size(); k++)
	{
		outfile << history[k].myname << " " << history[k].myscore << endl;//������ļ�
		cout << history[k].myname << "\t" << history[k].myscore << endl;
	}

	outfile.close();
}

void GAME::gameover()
{
	PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
	int x = 3, y = 8;
	
	printgameover(x, y);
	gotoxy(wall.getwidth() / 2 - 7, y + 9);
	cout << "SCORE: " << score;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//white

	gotoxy(0, wall.getheight() + 1);
	system("pause");
	printhistory();
}