#include "LevelManager.h"

LevelManager::LevelManager() {
	fTop = nullptr;
	fSize = 0;
}

void LevelManager::push(Level& aLevel) {
	SLLNode<Level>* newNode = new SLLNode<Level>(aLevel);

	//assign the new node to point to top node
	newNode->next = fTop;

	//assign new node as new top
	fTop = newNode;
	
	//increase stack size by 1
	fSize += 1;
}


void LevelManager::pop() {
	SLLNode<Level>* temp;

	//check if stack is empty
	if (isEmpty()) {
		cout << "Stack is underflow" << endl;
		return;
	}
	else {
		//assign the current top to temp
		temp = fTop;

		//assign top to the new top
		fTop = fTop->next;

		//remove the link between old top and new top
		temp->next = nullptr;

		//release old top from memory
		delete temp;

		//reduce size by 1
		fSize -= 1;
	}
}

//utility function to return the top of stack
SLLNode<Level>* LevelManager::get() {
	if (!isEmpty())
		return fTop;
	else
		return nullptr;
}

//utility function to check if the stack is empty
bool LevelManager::isEmpty() {
	if (fSize <= 0) {
		return true;
	}
	else {
		return false;
	}
}