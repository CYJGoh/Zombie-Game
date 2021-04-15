#pragma once
#include "Zombie.h"
#include "Player.h"
#include "Queue.h"
#include "AttackVisitor.h"

class LevelTree; //Forward declaration

class Level
{
private:
	string fName;
	Zombie fEnemyPresent;
	Weapon fWeaponDrop; //Weapon dropped at the end of level/map
	Player* fPlayer;
	Queue<string> fCollectibles; //Item dropped at the end of level/map

public:
	bool fCompleted;
	Level();
	Level(string aName, Weapon aWeaponDrop, Zombie aEnemy, Player* aPlayer, Queue<string> aCollectibles);

	//Accessors
	string getName();
	Zombie getEnemy();
	Weapon getWeapon();
	string getCollect();

	//Modifiers
	void setName(string aName);
	void setEnemy(Zombie aEnemy);
	void setWeaponDrop(Weapon aWeapon);
	void setCollectible(Queue<string> aCollect);

	void Fight(); //Player and Zombie attacking each other
	void Win(); //Operation after player win or zombie win
	void Escape(); //Player escape back to previous level/map
	void Display(); //Introduction of level/map
	void Battle(LevelTree* aTree); //Player and zombie battle action
	void DisplayItem(); //Display out all the collectibles for player to choose whether want to collect or not

	//accept visitor
	virtual void accept(ActionVisitor& v);
};

