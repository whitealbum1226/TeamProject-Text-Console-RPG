#pragma once

#include "Skill.h"

class Player;
class Monster;

class Blood : public Skill
{
public:
    Blood() : Skill("출혈", 30) {}

    virtual bool useSkill(Player& p, Monster& m) override;

    int GetBloodDamage() { return bloodDamage; }
    int GetBloodCount() { return bloodCount; }

    int SetBloodCount(int count) { return bloodCount = count; }

    void ShowDetail();

private:
    int bloodCount = 3; // 지속피해 턴
    int bloodDamage = 30; // 지속피해 데미지
};

