#include "Player.h"

Player::Player() {
	fName = "";
	fID = "";
	fMaxHP = fCurrentHP = 0;
	fDamageDealt = 0;
	fMaxShield = 0;
	fCurrentShield = 0;
	fArsenal = nullptr;
}

Player::Player(string aName, string aID, int aHP, Arsenal* aArsenal,  Inventory* aInventory) {
	fName = aName;
	fID = aID;
	fMaxHP = fCurrentHP = aHP;
	fDamageDealt = 10;
	fMaxShield = 50;
	fCurrentShield = 50; // first-time shield given to player
	fArsenal = aArsenal;
	fInventory = aInventory;
}

void Player::Attack(Character& aEnemy) {
	aEnemy.setCurrentHP(aEnemy.getCurrentHP() - fDamageDealt); //deduct enemy HP by the damage dealt by weapon equipped
	cout << aEnemy.getName() << " is damaged by " << fDamageDealt << endl;
}

void Player::Rest() {
	//check if player HP is not full, if yes, restore 20 HP, if not remind player is rested
	if (fCurrentHP < fMaxHP) {
		fCurrentHP += 20;
		cout << "You've rested. Healed 20 HP" << endl;
	}
	else if (fCurrentHP >= fMaxHP) {
		cout << "You're fully rested. Rest anymore cannot heal liao lah. Go kill some zombie." << endl;
	}

	//make sure the player's HP do not healed over the maximum HP
	if (fCurrentHP >= fMaxHP)
		fCurrentHP = fMaxHP;
}

void Player::EquipWeapon(int aWeaponIndex) {
	//set a temp node to top
	SLLNode<Weapon>* lNode = fArsenal->getTopNode();
	//look for the node at that index
	for (int i = 1; i < aWeaponIndex; i++) {
		lNode = lNode->next;
	}
	fWeaponEquipped = lNode->item; //change the weapon equipped to the item of that node
	fDamageDealt = fWeaponEquipped.getDamage(); //update the damage dealt
	cout << "Equipped " << fWeaponEquipped.getName() << endl;
}

void Player::StoreItem(Weapon aWeapon) {
	fArsenal->insertEnd(aWeapon);
}

void Player::StoreCollectibles(string aItem) {
	fInventory->StoreLast(aItem);
}

void Player::UseCollectibles(int aIndex) {
	//set a temp node to top
	DLLNode<string> lNode = *(fInventory->getTopNode());
	//look for the node at that index
	for (int i = 1; i < aIndex; i++) {
		lNode = lNode.getNext();
	}
	fCurrentShield = fMaxShield; //reset shield back to full
	fInventory->RemoveSelectedItem(lNode.getValue()); //remove the item with that index
	cout << "You used " << lNode.getValue() << " and your shield now is back to " << fMaxShield << endl;
}

Weapon Player::getWeapon() {
	return fWeaponEquipped;
}

int Player::getDamageDealt() {
	return fDamageDealt;
}

Arsenal* Player::getArsenal() {
	return fArsenal;
}

Inventory* Player::getInventory() {
	return fInventory;
}


void Player::setWeapon(Weapon aWeapon) {
	fWeaponEquipped = aWeapon;
}

void Player::setDamageDealt(int aDamage) {
	fDamageDealt = aDamage;
}

ostream& operator<<(ostream& aOStream, Player& aPlayer) {
	aOStream << "------------------------------------------------------" << endl;
	aOStream << "HP: " << aPlayer.fCurrentHP << "/" << aPlayer.fMaxHP << endl;
	aOStream << "Shield: " << aPlayer.fCurrentShield << "/" << aPlayer.fMaxShield << endl;
	aOStream << "Weapon Equipped: " << aPlayer.fWeaponEquipped.getName() << endl;
	aOStream << "Damage: " << aPlayer.fDamageDealt << endl;

	return aOStream;
}

//accept visitor
void Player::accept(ActionVisitor& v) {
	v.visit(*this);
}
