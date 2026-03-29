// BossDragon.h

#pragma once
#include "BossMonster.h"

class BossDragon :
    public BossMonster
{
public:
    BossDragon(int playerLevel);

    void TailSwing();
    void DownwardStrike();
    void FireBreath();
    void Roar();
    void HellFireBreath();
    void HellFireTailSwing();

    void UsePattern();
    void SpecialAttack() override;
};

