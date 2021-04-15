#pragma once
#include "DLLNode.h"
#include "ActionVisitor.h"
#include <iostream>
#include <string>

using namespace std;

class Inventory
{
private:
	DLLNode<string>* fTop;
	DLLNode<string> fSelected;
	DLLNode<string>* fEnd;
	int fSize;

public:
	Inventory();
	void StoreLast(string aItem);
	void StoreTop(string aItem);
	void StoreBefore(string aItem, DLLNode<string>* aBefore);
	void RemoveSelectedItem(string aItem);
	void RemoveItem();
	friend ostream& operator<<(ostream& aOStream, Inventory& aInven);

	//Accessors
	DLLNode<string>* getTopNode();
	DLLNode<string> getSelectedNode();
	DLLNode<string>* getEndNode();
	int Size();

	virtual void accept(ActionVisitor& v);
};

