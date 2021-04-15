#include "Arsenal.h"

Arsenal::Arsenal() {
	ftop = fSelected = nullptr;
	fSize = 0;
}

void Arsenal::insertWeapon(Weapon aWeapon, SLLNode<Weapon>* before) {
	SLLNode<Weapon>* newNode = new SLLNode<Weapon>(aWeapon);
	//newNode -> nextNode
	newNode->next = before->next; //the next node of the new node is assigned to the next node of the old node
	before->next = newNode; // the next node of the old node is assigned to the new node
	fSize++;
}

void Arsenal::insertTop(Weapon aWeapon) {
	SLLNode<Weapon>* newNode = new SLLNode<Weapon>(aWeapon, ftop); //next node of the new node assigned to top node
	ftop = newNode; //assign top node to the new node
	fSelected = ftop; //default selected node is the top node
	fSize++;
}

void Arsenal::insertEnd(Weapon aWeapon) {
	SLLNode<Weapon>** newNodePtr = &ftop;

	while (*newNodePtr != nullptr) {
		newNodePtr = &((*newNodePtr)->next); //assign the new node ptr to the NIL pointer at the end of the SLL
	}

	*newNodePtr = new SLLNode<Weapon>(aWeapon); //replace the NIL pointer to the new node
	fSize++;
}

SLLNode<Weapon>* Arsenal::getSelectedNode() {
	return fSelected;
}

SLLNode<Weapon>* Arsenal::getTopNode() {
	return ftop;
}

void Arsenal::next() {
	fSelected = fSelected->next;
}

int Arsenal::getSize() {
	return fSize;
}

ostream& operator<<(ostream& aOStream, Arsenal& aArsenal) {
	int count = 1;
	aArsenal.fSelected = aArsenal.ftop; //reset selected node to top node
	aOStream << "\nList of weapons: " << endl;
	
	while (aArsenal.fSelected != nullptr) {
		aOStream << "[" << count << "] " << aArsenal.fSelected->item << endl;
		aArsenal.fSelected = aArsenal.fSelected->next;
		count++;
	}
	aArsenal.fSelected = aArsenal.ftop; //reset selected node to top node

	return aOStream;
}