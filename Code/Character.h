#pragma once
#include <string>
#include <iostream>
#include "ActionVisitor.h"
using namespace std;

class Character
{
protected:
	string fName;
	string fID;
	int fMaxHP;
	int fCurrentHP;
	int fMaxShield;
	int fCurrentShield;

public:
	Character();
	virtual void Attack(Character& aChar) = 0; //The pure virtual method to be overridden by child classes
	
	//Accessors
	string getName();
	string getID();
	int getMaxHP();
	int getCurrentHP();
	int getMaxShield();
	int getCurrentShield();

	//Modifiers
	void setName(string aName);
	void setID(string aID);
	void setMaxHP(int aHP);
	void setCurrentHP(int aHP);
	void setMaxShield(int aShield);
	void setCurrentShield(int aShield);

	//Accept visitor
	virtual void accept(ActionVisitor& v);
};

