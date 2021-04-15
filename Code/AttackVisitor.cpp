#include "AttackVisitor.h"
#include "Player.h"
#include "Zombie.h"

//Constructor
AttackVisitor::AttackVisitor(int aDamage) {
	fDamage = aDamage;
}

//Attack player
void AttackVisitor::visit(Player& p) {
	//set player HP to be deducted by zombie's damage
	int lPlayerShield;

	lPlayerShield = p.getCurrentShield();
	if (lPlayerShield > 0) {
		lPlayerShield -= fDamage;
		p.setCurrentShield(lPlayerShield); //deduct shield if player shield is available

		//deduct player HP if damage dealt exceed sheild (shield went pass 0)
		if (lPlayerShield < 0) {
			p.setCurrentHP(p.getCurrentHP() - abs(lPlayerShield));
			p.setCurrentShield(0);
		}
	}
	else if (lPlayerShield <= 0) {
		p.setCurrentHP(p.getCurrentHP() - fDamage); //deduct player's health by damage dealt by zombie
	}

}

//Attack zombie
void AttackVisitor::visit(Zombie& z) {
	//set zombie HP to be deducted by player's damage
	cout << "----------------------------------------------------" << endl;
	z.setCurrentHP(z.getCurrentHP() - fDamage);
	cout << z.getName() << " damaged by " << fDamage << endl;
}