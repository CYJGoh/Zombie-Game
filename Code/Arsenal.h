#pragma once
#include "Weapon.h"
#include "SLLNode.h"

class Arsenal
{
private:
	SLLNode<Weapon>* ftop;
	SLLNode<Weapon>* fSelected;
	int fSize;

public:
	Arsenal();
	void insertWeapon(Weapon aWeapon, SLLNode<Weapon>* before);
	void insertTop(Weapon aWeapon);
	void insertEnd(Weapon aWeapon);
	void next();
	SLLNode<Weapon>* getSelectedNode();
	SLLNode<Weapon>* getTopNode();
	int getSize();
	friend ostream& operator<<(ostream& aOStream, Arsenal& aArsenal);
};

