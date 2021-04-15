#pragma once
#include "ActionVisitor.h"
class AttackVisitor :
    public ActionVisitor
{
private:
    int fDamage;

public:
    AttackVisitor(int aDamage);
    virtual void visit(Player& p);
    virtual void visit(Zombie& z);
};

