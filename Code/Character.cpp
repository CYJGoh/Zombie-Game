#include "Character.h"

Character::Character() {
	fName = "";
	fID = "";
	fMaxHP = fCurrentHP = 0;
	fMaxShield = fCurrentShield = 0;
}

string Character::getName() {
	return fName;
}

string Character::getID() {
	return fID;
}

int Character::getMaxHP() {
	return fMaxHP;
}

int Character::getCurrentHP() {
	return fCurrentHP;
}

int Character::getMaxShield() {
	return fMaxShield;
}

int Character::getCurrentShield() {
	return fCurrentShield;
}


void Character::setName(string aName) {
	fName = aName;
}

void Character::setID(string aID) {
	fID = aID;
}

void Character::setMaxHP(int aHP) {
	fMaxHP = aHP;
}

void Character::setCurrentHP(int aHP) {
	fCurrentHP = aHP;
}

void Character::setMaxShield(int aShield) {
	fMaxShield = aShield;
}

void Character::setCurrentShield(int aShield) {
	fCurrentShield = aShield;
}

void Character::accept(ActionVisitor& v) {
	v.visit(*this);
}
