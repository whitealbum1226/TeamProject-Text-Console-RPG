// BossMonster.cpp

#include "BossMonster.h"

BossMonster::BossMonster(const std::string& name, int playerLevel)
    : Monster(name, playerLevel), isPhaseTwo_(false), turnCount_(0)
{
    // 보스몹 평균 기본 스탯
    // 내부에서 추가 구현시 곱연산 가능!!
    hp_ *= 3;
    maxHp_ = hp_;

    attack_ *= 2;
    defense_ *= 2;
}

void BossMonster::TakeDamage(int takeDamage)
{
    Monster::TakeDamage(takeDamage);

    if (!isPhaseTwo_ && hp_ <= maxHp_ / 2)
        // 보스 체력이 반 이하가 되면 2페이지 돌입
    {
        isPhaseTwo_ = true;
        std::cout << "\n==========================\n";
        std::cout << "    강력한 분노가 느껴진다!!     ";
        std::cout << "  " << name_ << " 이(가) 2 페이즈에 돌입했다!!\n";
        std::cout << "==========================\n\n";
        
    }
}

bool BossMonster::IsPhaseTwo() const
{
    return isPhaseTwo_;
}

void BossMonster::IncreaseTurnCount()
{
    ++turnCount_;
    // 스킬 공격에 사용될 예정
}

int BossMonster::GetTurnCount() const
{
    return turnCount_;
}
