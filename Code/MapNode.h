#pragma once
#include <stdexcept>

using namespace std;

template <class T>
class MapNode
{
private:
	//Keep track of the child nodes branched from this node
	MapNode<T>* fLeft;
	MapNode<T>* fRight;

	//Keep track of the parent node
	MapNode<T>* fParent;

	T* fData;

	//Default private constructor
	MapNode() {
		//initialises all the fields
		fData = (T*)0; //sets the data to nullptr

		//sets left / right / parent to NIL
		fLeft = &NIL;
		fRight = &NIL;
		fParent = &NIL;
	}

public:
	//Sentinel node
	static MapNode<T> NIL;

	//Constructor that initialises all the map info and sets the left and right node to NIL
	MapNode(T* aData) {
		fData = aData;

		//sets left / right / parent to NIL
		fLeft = &NIL;
		fRight = &NIL;
		fParent = &NIL;
	}

	//Destructor that deletes the node
	~MapNode() {
		if (fLeft != &NIL)
			delete fLeft;

		if (fRight != &NIL)
			delete fRight;

		if (fParent != &NIL)
			delete fParent;
	}

	//Auxialiary methods

	//return if this node is NIL
	bool isEmpty() const {
		return this == &NIL;
	}

	//return entity present
	T getData() {
		return *fData;
	}

	//return left node
	MapNode<T>& left() const {
		//if left node is not empty, then return node
		if (isEmpty())
			throw domain_error("Empty node!");

		return *fLeft;
	}

	//return right node
	MapNode<T>& right() const {
		//if right node is not empty, then return node
		if (isEmpty())
			throw domain_error("Empty node!");

		return *fRight;
	}

	//return parent node
	MapNode<T>& parent() const {
		//if parent node is not empty, then return node
		if (isEmpty())
			throw domain_error("Empty node!");

		return *fParent;
	}

	//Attachment methods
	//Attaching a node to left or right
	void attachLeft(MapNode<T>* aNode) {
		//check if the node is empty
		if (isEmpty())
			throw domain_error("Empty node!");

		//check if the left has already contained a node
		if (fLeft != &NIL)
			throw domain_error("This node is occupied!");

		//attaches node to left 
		fLeft = aNode;

		//set parent of new node as this node
		fLeft->fParent = this;
	}

	void attachRight(MapNode<T>* aNode) {
		//check if the node is empty
		if (isEmpty())
			throw domain_error("Empty node!");

		//check if the left has already contained a node
		if (fRight != &NIL)
			throw domain_error("This node is occupied!");

		//attaches node to right 
		fRight = aNode;

		//set parent of new node as this node
		fRight->fParent = this;
	}

	//Detachment methods
	//Detaching a node from left or right
	MapNode<T>* detachLeft() {
		//check if the node is empty
		if (isEmpty())
			throw domain_error("Empty node!");

		MapNode<T>& temp = *fLeft; //store the left node to temp
		fLeft->fParent = &NIL; // remove parent of detached node
		fLeft = &NIL; //set left back to NIL
		return &temp; //return the detached node
	}
	MapNode<T>* detachRight() {
		//check if the node is empty
		if (isEmpty())
			throw domain_error("Empty node!");

		MapNode<T>& temp = *fRight; //store the right node to temp
		fRight->fParent = &NIL; // remove parent of detached node
		fRight = &NIL; //set right back to NIL
		return &temp; //return the detached node
	}
};

//Implements the NIL node
template <class T>
MapNode<T> MapNode<T>::NIL;