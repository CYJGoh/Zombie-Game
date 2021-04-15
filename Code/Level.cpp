#include "Level.h"
#include "LevelTree.h"

Level::Level() {}

Level::Level(string aName, Weapon aWeaponDrop, Zombie aEnemy, Player* aPlayer, Queue<string> aCollectibles) {
	fName = aName;
	fEnemyPresent = aEnemy;
	fWeaponDrop = aWeaponDrop;
	fPlayer = aPlayer;
	fCompleted = false;
	fCollectibles = aCollectibles;
}

string Level::getName() {
	return fName;
}

Zombie Level::getEnemy() {
	return fEnemyPresent;
}

Weapon Level::getWeapon() {
	return fWeaponDrop;
}

string Level::getCollect() {
	return (*fCollectibles.GetFront()).item;
}

void Level::setName(string aName) {
	fName = aName;
}

void Level::setEnemy(Zombie aEnemy) {
	fEnemyPresent = aEnemy;
}

void Level::setWeaponDrop(Weapon aWeapon) {
	fWeaponDrop = aWeapon;
}

void Level::setCollectible(Queue<string> aCollect) {
	fCollectibles = aCollect;
}

//Fight between player and zombie
void Level::Fight() {
	AttackVisitor attackByZombie = AttackVisitor(fEnemyPresent.getDamage());
	AttackVisitor attackByPlayer = AttackVisitor(fPlayer->getDamageDealt());

	fEnemyPresent.accept(attackByPlayer); //player attacks zombie
	//fPlayer->Attack(fEnemyPresent); 

	//Ensure the lower limit of the enemy's HP is fixed at 0
	if (fEnemyPresent.getCurrentHP() < 0) {
		fEnemyPresent.setCurrentHP(0);
	}
	cout << "Enemy HP: " << fEnemyPresent.getCurrentHP() << endl;

	fPlayer->accept(attackByZombie); //zombie attacks player
	//fEnemyPresent.Attack(*fPlayer); 
	cout << "Your HP: " << fPlayer->getCurrentHP() << "\n" << endl;
}

void Level::Win() {
	string lUserInput;

	//Spawning new weapon and automatically stored into arsenal but not equipped yet
	cout << "Congrats! You beaten " << fEnemyPresent.getName() << endl;
	cout << "You found " << fWeaponDrop.getName() << endl;
	cout << "It can deal " << fWeaponDrop.getDamage() << " damage" << endl;
	cout << "It is now stored into your arsenal\n" << endl;
	fPlayer->StoreItem(fWeaponDrop);

	//Collectible spawning
	DisplayItem();
	/*cout << "\nYou found " << fCollectibles << " on the ground" << endl;
	cout << "Do you wish to collect it? [yes/no]" << endl;
	cin >> lUserInput;
	if (lUserInput == "yes") {
		fPlayer->StoreCollectibles(fCollectibles); //Store collectible into inventory
		cout << "You've managed to store " << fCollectibles << " into your collectibles inventory.\n" << endl;
	}
	else if (lUserInput == "no") {
		cout << "Haih! Give you free stuff to collect also don't want. Okay, fine." << endl;
	}
	else {
		cout << "Aiya type properly lah!" << endl;
	}*/
	fCompleted = true;
}

//Display message and return back to main loop
void Level::Escape() {
	cout << "You managed to retreat and reach your previous location\n" << endl;
}

//Status of level
void Level::Display() {
	cout << "\nYou have reached " << fName << endl;
	cout << "A wild " << fEnemyPresent.getName() << " appeared." << endl;
	cout << "It has a initial HP of " << fEnemyPresent.getMaxHP() << endl;
}

//Scene of battling between player and zombie
void Level::Battle(LevelTree* aTree) {
	string lUserInput3;

	fEnemyPresent.setCurrentHP(fEnemyPresent.getMaxHP()); //reset the enemy HP to original HP

	while (true)
	{
		//Check if enemy died or player died
		if (fEnemyPresent.getCurrentHP() <= 0) {
			Win(); //Player win if manage to defeat zombie
			break;
		}
		else if (fPlayer->getCurrentHP() <= 0) {
			cout << "Sadly, you died. So fast die already? Haiya. Get good lah. " << endl;
			aTree->Parent();
			break;
		}

		cout << "\nChoose an action [fight/escape]" << endl; //Displaying options available to be use
		cin >> lUserInput3;

		//User input result
		if (lUserInput3 == "fight") {
			if (fEnemyPresent.getCurrentHP() > 0) {
				Fight(); //Fight between player and zombie
			}
		}
		else if (lUserInput3 == "escape") {
			Escape(); 
			aTree->Parent();
			break; //Player escape to previous map (level)
		}
		else {
			cout << "Aiyo type properly lah!" << endl;
		}
	}
}

void Level::DisplayItem() {
	string lUserInput;
	while (fCollectibles.GetFront() != nullptr) {
		cout << "\nYou found " << (*fCollectibles.GetFront()).item << endl;
		while (true) {
		cout << "Do you want to collect it into your inventory?" << endl;
			cin >> lUserInput;
			if (lUserInput == "yes") {
				fPlayer->StoreCollectibles(fCollectibles.GetFront()->item);
				cout << "You have succefully collected " << fCollectibles.Dequeue()->item << endl;
				break;
			}
			else if (lUserInput == "no") {
				cout << "Okay. You threw " << fCollectibles.Dequeue()->item << " away." << endl;
				break;
			}
			else {
				cout << "That input cannot be accepted" << endl;
			}
		}
	}
}

//accept visitor
void Level::accept(ActionVisitor& v) {
	v.visit(*this);
}
