#pragma once
//Forward declarations
class Character;
class Player;
class Zombie;
class Level;
class Inventory;

class ActionVisitor
{
public:
	virtual void visit(Character& c);
	virtual void visit(Player& p);
	virtual void visit(Zombie& z);
	virtual void visit(Level& l);
	virtual void visit(Inventory& i);
};

