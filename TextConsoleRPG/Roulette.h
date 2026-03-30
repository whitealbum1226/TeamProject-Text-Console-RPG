#pragma once

#include "Skill.h"

class Player;
class Monster;

class Roulette : public Skill
{
public:
    Roulette() : Skill("운명의 룰렛", 50) {}

    virtual bool useSkill(Player& p, Monster& m) override;

    void ShowDetail();
};
