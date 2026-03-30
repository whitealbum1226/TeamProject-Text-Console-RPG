#pragma once
#include "Skill.h"

class Player;
class Monster;

class Boom : public Skill
{
public:
    Boom() : Skill("폭발", 50) {}

    virtual bool useSkill(Player& p, Monster& m) override;
};
