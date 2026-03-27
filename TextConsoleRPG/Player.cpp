//Player.cpp

#include "Player.h"

// 플레이어 생성자 설정
Player::Player(const std::string& name)
    : name_(name), job_("용사"), level_(1), hp_(300), attack_(40), exp_(0)
{
}

std::string Player::GetName() const
{
    return name_;
}

std::string Player::GetJob() const
{
    return job_;
}

int Player::GetLevel() const
{
    return level_;
}

int Player::GetHP() const
{
    return hp_;
}

int Player::GetAttack() const
{
    return attack_;
}

int Player::GetExp() const
{
    return exp_;
}

void Player::SetName(std::string name)
{
    this->name_ = name;
}

void Player::SetJob(std::string job)
{
    this->job_ = job;
}

void Player::SetLevel(int level)
{
    this->level_ = level;
}

void Player::SetHP(int hp)
{
    this->hp_ = hp;
}

void Player::SetAttack(int attack)
{
    this->attack_ = attack;
}

void Player::SetExp(int exp)
{
    this->exp_ = exp;
}
void Player::TakeDamage(int takeDamage)
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
