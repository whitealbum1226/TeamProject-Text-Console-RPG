#pragma once

#include "Skill.h"

class Player;
class Monster;

class ManaBurn : public Skill
{
public:
    ManaBurn() : Skill("마나 익스플로전", 0) {}

    virtual bool useSkill(Player& p, Monster& m) override;

    void ShowDetail();
};
