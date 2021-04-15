#include "Inventory.h"

Inventory::Inventory() {
	fTop = nullptr;
	fSelected = DLLNode<string>::NIL;
	fEnd = nullptr;
	fSize = 0;
}

void Inventory::StoreLast(string aItem) {
	DLLNode<string>* newNode = new DLLNode<string>(aItem);
	fEnd->append(*newNode);
	fEnd = newNode;
	fSize += 1;
	fSelected = *fTop; //reset selected back to the top
}

void Inventory::StoreTop(string aItem) {
	DLLNode<string>* newNode = new DLLNode<string>(aItem);
	if (fTop != nullptr) {
		fTop->prepend(*newNode);
		fTop = newNode;
	}
	else {
		fTop = newNode;
		fEnd = newNode;
	}
	
	//assign end node to fEnd
	while (fSelected.getNext() != DLLNode<string>::NIL) {
		fEnd = &fSelected;
		fSelected = fSelected.getNext();
	}
	fSelected = *fTop; //reset selected back to the top
	fSize += 1;
}

void Inventory::StoreBefore(string aItem, DLLNode<string>* aBefore) {
	DLLNode<string>* newNode = new DLLNode<string>(aItem);
	aBefore->prepend(*newNode);	
	fSize += 1;
	if (fTop == aBefore) {
		fTop = newNode;
	}
	fSelected = *fTop; //reset selected back to the top
}

void Inventory::RemoveSelectedItem(string aItem) {
	//Find the value that matches aItem then remove it
	for (int i = 0; i < fSize; i++) {
		if (fSelected.getValue() == aItem) {
			fSelected.remove();
			if (fSelected.getNext() == DLLNode<string>::NIL) {
				fEnd = &fSelected.getPrevious();
			}
			else if (fSelected.getPrevious() == DLLNode<string>::NIL) {
				fTop = &fSelected.getNext();
			}
			break;
		}
		fSelected = fSelected.getNext();
	}
	fSize -= 1;
	fSelected = *fTop; //reset selected back to the top
}

//Remove last item
void Inventory::RemoveItem() {
	DLLNode<string>* temp = fEnd;
	fEnd = &fEnd->getPrevious();

	temp->remove();
	fSize -= 1;
	cout << "The item has been removed." << endl;
}

ostream& operator<<(ostream& aOStream, Inventory& aInven) {
	string lUserInput;

	if (aInven.fTop != nullptr && aInven.fSize != 0) {
		aOStream << "Items in inventory: " << endl;
		for (int i = 0; i < aInven.fSize; i++) {
			aOStream << "[" << i + 1 << "] " << aInven.fSelected.getValue() << endl;
			aInven.fSelected = aInven.fSelected.getNext();
		}
		aInven.fSelected = *(aInven.fTop);

		//Give user option to remove the most recently stored item stored into inventory 
		aOStream << "For some reason, do you wish to remove your previously collected item? [yes/no]" << endl;
		cin >> lUserInput;
		if (lUserInput == "yes") {
			aInven.RemoveItem();
			aOStream << "You've managed to remove the item. " << endl;
		}
		else if (lUserInput == "no") {
			aOStream << "Okay!" << endl;
		}
		else {
			aOStream << "Aiyo type properly lah!" << endl;
		}
	}
	else {
		aOStream << "You have nothing in your inventory yet lah. Nothing to see. Go kill zombie first." << endl;
	}

	return aOStream;
}

DLLNode<string>* Inventory::getTopNode() {
	return fTop;
}

DLLNode<string> Inventory::getSelectedNode() {
	return fSelected;
}

DLLNode<string>* Inventory::getEndNode() {
	return fEnd;
}

int Inventory::Size() {
	return fSize;
}

void Inventory::accept(ActionVisitor& v) {
	v.visit(*this);
}
