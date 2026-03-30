#pragma once
#include "Skill.h"

class Player;
class Monster;

class MultiStrike : public Skill
{
public:
    MultiStrike() : Skill("연속 공격", 50) {}

    virtual bool useSkill(Player& p, Monster& m) override;
};
