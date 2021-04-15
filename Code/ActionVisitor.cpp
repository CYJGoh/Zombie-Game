#include "ActionVisitor.h"
#include "Player.h"
#include "Zombie.h"
#include "Level.h"
#include "Inventory.h"

void ActionVisitor::visit(Character& c) {}
void ActionVisitor::visit(Player& p) {}
void ActionVisitor::visit(Zombie& z) {}
void ActionVisitor::visit(Level& l) {}
void ActionVisitor::visit(Inventory& i) {}