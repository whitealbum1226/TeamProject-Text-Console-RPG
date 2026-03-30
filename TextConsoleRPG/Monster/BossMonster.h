// BossMonster.h

#pragma once
#include "Monster.h"

class BossMonster :
    public Monster
{
public:
    BossMonster(const std::string& name, int playerLevel);

    void TakeDamage(int takeDamage) override;
    bool IsPhaseTwo() const;
    virtual void SpecialAttack() = 0; // 스킬공격 순수가상함수
    void IncreaseTurnCount();
    int GetTurnCount() const;

protected:
    bool isPhaseTwo_;
    int turnCount_;
};

