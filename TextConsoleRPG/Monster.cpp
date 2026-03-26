// Monster.cpp

#include "Monster.h"
#include <cstdlib>
#include <ctime>

// 몬스터 생성자
Monster::Monster(const std::string name, int playerLevel)
    : name_(name), hp_(0), attack_(0), defense_(0)
{
    static bool randInitialized = false;
    if (!randInitialized) // rand 초기화
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        randInitialized = true;
    }
    // 플레이어 레벨 값에 따른 랜덤 스텟
    int minHp = playerLevel * 20;
    int maxHp = playerLevel * 30;
    hp_ = rand() % (maxHp - minHp + 1) + minHp;

    int minAtk = playerLevel * 5;
    int maxAtk = playerLevel * 10;
    attack_ = rand() % (maxAtk - minAtk + 1) + minAtk;

    defense_ = playerLevel * 3;
}

std::string Monster::GetName() const
{
    return name_;
}
int Monster::GetHP() const
{
    return hp_;
}
int Monster::GetAttack() const
{
    return attack_;
}
int Monster::GetDefense() const
{
    return defense_;
}

void Monster::SetName(std::string name)
{
    this->name_ = name;
}
void Monster::SetHP(int hp)
{
    this->hp_ = hp;
}
void Monster::SetAttack(int attack)
{
    this->attack_ = attack;
}
void Monster::SetDefense(int defense)
{
    this->defense_ = defense;
}

// 몬스터가 데미지를 입을 때 함수 처리
void Monster::TakeDamage(int takeDamage)
{
    if (takeDamage <= 0)
    {
        takeDamage = 1;
    }

    hp_ -= takeDamage;

    if (hp_ < 0)
    {
        hp_ = 0;
    }
}

// 몬스터가 HP 0인지 확인하고 사망 여부 true/false 를 반환
bool Monster::IsDead() const
{
    return hp_ == 0;
}
