#include"food.h"
#include"wall.h"
extern void gotoxy(int x, int y);

/*FOOD*/
void FOOD::set_loc()
{
	WALL wall;
	srand(time(NULL));
	food_x = rand() % (wall.getwidth() - 2) + 1;
	if (food_x == wall.getwidth() - 2)
		food_x--;
	if (food_x == 1)
		food_x++;

	food_y = rand() % (wall.getheight() - 2) + 1;
}
void FOOD::print_food()
{
	//blue
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_BLUE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//青色
	gotoxy(food_x, food_y);
	cout << "*";
	//set back to white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

	if (rfood_x == wall.getwidth() - 2)
		rfood_x--;
	if (rfood_x == 1)
		rfood_x++;

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
