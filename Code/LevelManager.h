#pragma once
#include "Level.h"
#include "DLLNode.h"
#include "SLLNode.h"

class LevelManager
{
private:
	SLLNode<Level>* fTop;
	int fSize;

public:
	LevelManager();
	void push(Level& aLevel); //insert into stack
	void pop(); //remove from stack
	SLLNode<Level>* get(); //return last stored item
	bool isEmpty(); //checks if the stack is empty
};