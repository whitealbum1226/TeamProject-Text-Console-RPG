#pragma once

#include "Skill.h"

class Player;
class Monster;

class QuickAttack : public Skill
{
public:
    QuickAttack() : Skill("신속", 10) {}

    virtual bool useSkill(Player& p, Monster& m) override;
};
