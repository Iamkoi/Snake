#include"snake.h"
#include"wall.h"

extern void gotoxy(int x, int y);

void SNAKE::print_node(int x, int y)//print node
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//white
	gotoxy(x, y);
	cout << "*";
}

void SNAKE::delete_node(int x, int y)//print node
{
	for (int i = 0; i < body.size() - 1; i++)
	{
		if (body[i].x == x && body[i].y == y)//蛇尾与蛇身有交叠，不删除蛇尾位置的‘*’
			return;
	}
	gotoxy(x, y);
	cout << " ";
}

void SNAKE::initial_snake()//initial snake
{
	SNAKE::Node node1, node2, node3;
	WALL wall;
	node1.x = wall.getwidth() / 2;
	node2.x = wall.getwidth() / 2;
	node3.x = wall.getwidth() / 2;

	node1.y = wall.getheight() / 2;
	node2.y = node1.y - 1;
	node3.y = node2.y - 1;

	body.push_back(node1);
	body.push_back(node2);
	body.push_back(node3);

	for (int i = 0; i < body.size(); i++)
		print_node(body[i].x, body[i].y);
}

void SNAKE::move()//4 directions
{
	SNAKE::Node *node = new SNAKE::Node;
	switch (direction)
	{
	case 1:
		node->x = body[0].x + 1;
		node->y = body[0].y;
		break;
	case 2:
		node->x = body[0].x;
		node->y = body[0].y + 1;
		break;
	case 3:
		node->x = body[0].x - 1;
		node->y = body[0].y;
		break;
	case 4:
		node->x = body[0].x;
		node->y = body[0].y - 1;
		break;
	}
	body.insert(body.begin(), node[0]);//插入蛇头（蛇头向前）

	if (delete_tail == 1)//删除蛇尾
	{
		delete_node(body[body.size() - 1].x, body[body.size() - 1].y);
		body.erase(body.end() - 1);
	}

	print_node(body[0].x, body[0].y);

}

SNAKE::Node SNAKE::head() const//the snake's head
{
	SNAKE::Node node;
	node.x = body[0].x;
	node.y = body[0].y;
	return node;
}
