#pragma once
#include "Skill.h"

class Player;
class Monster;

class Slash : public Skill
{
public:
    Slash() : Skill("슬래시", 20) {}

    virtual bool useSkill(Player& p, Monster& m) override;
};
