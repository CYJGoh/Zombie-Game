#pragma once
#include "Character.h"
#include "Weapon.h"
#include "Arsenal.h"
#include "Inventory.h"

class Player :
    public Character
{
private:
    Weapon fWeaponEquipped;
    int fDamageDealt;
    Arsenal* fArsenal;
    Inventory* fInventory;

public:
    Player();
    Player(string aName, string aID, int aHP, Arsenal* aArsenal, Inventory* aInventory);
    void Attack(Character& aEnemy); //Damage according to what weapon equipped
    void Rest(); //Replenish health
    void EquipWeapon(int aWeaponIndex); //Equip weapon from inventory, update damage dealt
    void StoreItem(Weapon aWeapon); //Store weapon into arsenal
    friend ostream& operator<<(ostream& aOStream, Player& aPlayer); //Display weapons equipped and health left
    void StoreCollectibles(string aItem); //Store collectibles into inventory
    void UseCollectibles(int aIndex); //Use collectibles in inventory to refill shield

    //Accessors
    Weapon getWeapon();
    int getDamageDealt();
    Arsenal* getArsenal();
    Inventory* getInventory();

    //Modifiers
    void setWeapon(Weapon aWeapon);
    void setDamageDealt(int aDamage);

    //accept visitor
    virtual void accept(ActionVisitor& v);
};

