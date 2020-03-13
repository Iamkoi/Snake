//#include"game.h"
#include"wall.h"

extern void gotoxy(int x, int y);

void WALL::print_wall()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//青色
	//上边界
	gotoxy(0, 0);
	for (int i = 0; i < width; i += 2)
		cout << "■";

	//下边界
	gotoxy(0, height - 1);
	for (int i = 0; i < width; i += 2)
		cout << "■";

	//左右边界
	//gotoxy(0, 1);
	for (int i = 1; i < height - 1; i++)
	{
		gotoxy(0, i);
		cout << "■";
		gotoxy(width - 2, i);
		cout << "■";
	}

	gotoxy(0, height);

	//set back to white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int WALL::getwidth() const
{
	return width;
}

int WALL::getheight() const
{
	return height;
}