#include "LevelTree.h"

//constructor
LevelTree::LevelTree() {
	//initialiases all the fields
	fRootRoom = &(MapNode<Level>::NIL);
	fCurrentRoom = &(MapNode<Level>::NIL);
	fSize = 0;
}

//insert a node to the left of the current pointed node
void LevelTree::InsertLeft(Level& aData) {
	//create new level node
	MapNode<Level>* node = new MapNode<Level>(&aData);

	//check if root is not assigned
	if (fRootRoom == &(MapNode<Level>::NIL)) {
		//store new node as root and current node points at root node
		fRootRoom = node;
		fCurrentRoom = fRootRoom;
	}
	else {
		//attach to the left of current node and update current node to point at new node
		fCurrentRoom->attachLeft(node);
		fCurrentRoom = &fCurrentRoom->left();
	}
	//increase size of tree by 1
	fSize += 1;
}

//insert a node that is already created to the left of current node
void LevelTree::InsertLeft(MapNode<Level>* aNode) {
	//attach existing node to the left of current node
	fCurrentRoom->attachLeft(aNode);
	fCurrentRoom = &fCurrentRoom->left();
}

//insert a node to the right of the current pointed node
void LevelTree::InsertRight(Level& aData) {
	//create new level node
	MapNode<Level>* node = new MapNode<Level>(&aData);

	//check if root is not assigned
	if (fRootRoom == &(MapNode<Level>::NIL)) {
		//store new node as root and current node points at root node
		fRootRoom = node;
		fCurrentRoom = fRootRoom;
	}
	else {
		//attach to the right of current node and update current node to point at new node
		fCurrentRoom->attachRight(node);
		fCurrentRoom = &fCurrentRoom->right();
	}
	//increase size of tree by 1
	fSize += 1;
}

//insert a node that is already created to the right of current node
void LevelTree::InsertRight(MapNode<Level>* aNode) {
	//attach existing node to the right of current node
	fCurrentRoom->attachRight(aNode);
	fCurrentRoom = &fCurrentRoom->right();
}

//remove the left node of the pointed node
MapNode<Level>* LevelTree::DeleteLeft() {
	//decrease size of tree by 1
	fSize -= 1;
	//detach the left child node and return it back
	return fCurrentRoom->detachLeft();;
}

//remove the right node of the pointed node
MapNode<Level>* LevelTree::DeleteRight() {
	//decrease size of tree by 1
	fSize -= 1;
	//detach the right child node and return it back
	return fCurrentRoom->detachRight();
}

//remove root node 
MapNode<Level>* LevelTree::DeleteRoot() {
	//decrease size of tree by 1
	fSize -= 1;

	//store root node into temp 
	MapNode<Level>& temp = *fRootRoom;
	//set root to point to NIL
	fRootRoom = &MapNode<Level>::NIL;
	//return root node
	return &temp;
}

//return the total nodes in the tree
int LevelTree::Size() {
	return fSize;
}

//return root node
MapNode<Level>& LevelTree::getRoot() {
	return *fRootRoom;
}

//return current pointed node
MapNode<Level>& LevelTree::getCurrent() {
	return *fCurrentRoom;
}

//Tree traversal
//change the current node to point to left node
MapNode<Level>& LevelTree::Left() {
	//point current node to the left child node
	fCurrentRoom = &fCurrentRoom->left();
	return *fCurrentRoom;
}

//change the current node to point to right node
MapNode<Level>& LevelTree::Right() {
	//point current node to the right child node
	fCurrentRoom = &fCurrentRoom->right();
	return *fCurrentRoom;
}

//change the current node to point to previous node
MapNode<Level>& LevelTree::Parent() {
	fCurrentRoom = &fCurrentRoom->parent();
	return *fCurrentRoom;
}

//change the current node to point back to the root
void LevelTree::Reset() {
	//set current node back to root
	fCurrentRoom = fRootRoom;
}