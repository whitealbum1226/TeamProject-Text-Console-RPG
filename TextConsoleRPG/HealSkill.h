#pragma once

#include "Skill.h"

class Player;
class Monster;

class HealSkill : public Skill
{
public:
    HealSkill() : Skill("회복", 20) {}

    virtual bool useSkill(Player& p, Monster& m) override;
};
