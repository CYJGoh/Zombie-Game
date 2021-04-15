#pragma once

template<class T>
class DLLNode
{
private:
	T fValue;
	DLLNode<T>* fNext;
	DLLNode<T>* fPrevious;
	
public:
	//Sentinel node/NIL node
	static DLLNode<T> NIL;
	
	DLLNode() {
		fValue = T();
		fNext = &NIL;
		fPrevious = &NIL;
	}

	DLLNode( const T& aValue ) {
		fValue = aValue;
		//both pointers point to NIL when node is created
		fNext = &NIL;
		fPrevious = &NIL;
	}

	//Add a node before this node
	void prepend(DLLNode<T>& aNode ) {
		
		aNode.fNext = this; //assign this node to the next node of the new node 

		//checks if there is a node before this node
		if(fPrevious != &NIL) {
			//previous<->this, becomes previous<->aNode<->this
			//assign the prev of this node to the prev node of new node
			aNode.fPrevious = fPrevious;
			//now the previous->aNode
			fPrevious->fNext = &aNode;
		}
		//assign the new node as the previos of this node
		fPrevious = &aNode;
	}

	//Add a node after this node
	void append(DLLNode<T>& aNode ) {
		aNode.fPrevious = this; //asign this node as the previous of the new node

		//checks if the there is a node after this node
		if(fNext != &NIL){
			//this<->next, change to this<->aNode<->next
			//assign the next node of this node to the next node of new node
			aNode.fNext = fNext;
			//now next points backwards to aNode, aNode<-next
			fNext->fPrevious = &aNode; 
		}

		//assign the new node as the next of this node
		fNext = &aNode; 
	}

	//Remove this node
	void remove() {
		//previous<->this<->next, to previous<->next with this pointing to NIL in front and behind
		
		//Check if fNext/fPrevious are NIL
		if(fNext == &NIL) { 
			//make the next node of previous as NIL
			fPrevious->fNext = &NIL;
		}
		else if(fPrevious == &NIL) {
			//make the previous node of next as NIL
			fNext->fPrevious = &NIL;
		}
		else {
			//If both previous and next exist
			fPrevious->fNext = fNext; // from previous->this->next to previous->next
			fNext->fPrevious = fPrevious; // from previous<-this<-next to previous<-next
		}
	}

	//accessors
	T& getValue() { 
		return fValue; 
	}

	DLLNode<T>& getNext() {
		return *fNext; 
	}
	DLLNode<T>& getPrevious() {
		return *fPrevious; 
	}

	//equivalence operator overload for DLL nodes
	bool operator==(const DLLNode<T>& aOther) const {
		return fValue == aOther.fValue;
	}

	bool operator!=(const DLLNode<T>& aOther) const {
		return !(*this == aOther);
	}
};

//Definition for NIL node
template<class T>
DLLNode<T> DLLNode<T>:: NIL;
