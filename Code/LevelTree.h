#pragma once
#include "MapNode.h"
#include "Level.h"

using namespace std;
class LevelTree
{
private:
	MapNode<Level>* fRootRoom;
	MapNode<Level>* fCurrentRoom;
	int fSize;

public:
	LevelTree();

	//insert a node to the left of the current pointed node
	void InsertLeft(Level& aData);
	void InsertLeft(MapNode<Level>* aNode);

	//insert a node to the right of the current pointed node
	void InsertRight(Level& aData);
	void InsertRight(MapNode<Level>* aNode);

	MapNode<Level>* DeleteLeft(); //remove the left node of the pointed node
	MapNode<Level>* DeleteRight(); //remove the right node of the pointed node
	MapNode<Level>* DeleteRoot(); //remove root node 

	int Size(); //return the total nodes in the tree

	MapNode<Level>& getRoot(); //return root node
	MapNode<Level>& getCurrent(); //return current pointed node

	//Tree traversal
	MapNode<Level>& Left(); //change the current node to point to left node
	MapNode<Level>& Right(); //change the current node to point to right node
	MapNode<Level>& Parent(); //change the current node to point to previous node
	void Reset(); //change the current node to point back to the root
};