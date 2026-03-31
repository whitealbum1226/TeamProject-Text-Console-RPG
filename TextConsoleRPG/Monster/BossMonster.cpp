// BossMonster.cpp

#include "BossMonster.h"
#include <iomanip>

BossMonster::BossMonster(const std::string& name, int playerLevel)
    : Monster(name, playerLevel), isPhaseTwo_(false), turnCount_(0)
{
   // 보스 기본 스탯 뻥튀기
    // 해당 객체 내부에서 곱연산도 가능
    hp_ *= 3;
    maxHp_ = hp_;

    attack_ *= 2;
    defense_ *= 2;
}

void BossMonster::TakeDamage(int takeDamage)
{
    Monster::TakeDamage(takeDamage);

    // 보스 체력이 반 이하가 되면 2페이즈 돌입
    if (!isPhaseTwo_ && hp_ <= maxHp_ / 2)
    {
        isPhaseTwo_ = true;
        std::cout << "\n===============================\n";
        std::cout << std::setw(30) << "강력한 분노가 느껴진다!!\n";
        std::cout << std::setw(8) << name_ << " 이(가) 2 페이즈에 돌입했다!!\n";
        std::cout << "===============================\n\n";
        // 다른 파일에서 테스트 해보면서 제일 깔끔한 출력 결과물
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
