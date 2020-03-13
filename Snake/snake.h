#ifndef SNAKE_H
#define SNAKE_H

#include<vector>
#include<iostream>
//#include"game.h"
using namespace std;

class SNAKE
{
private:
	struct Node{
		int x, y;
	};
	vector<Node> body;
public:
	int speed = 150;
	int direction = 2;//¡ú:1		¡ý:2		¡û:3		¡ü:4
	bool delete_tail = 1;//if clean the tail when moving
	void print_node(int x, int y);//print node
	void delete_node(int x, int y);//print node
	void initial_snake();//initial snake
	void move();//4 directions
	Node head() const;
};

#endif