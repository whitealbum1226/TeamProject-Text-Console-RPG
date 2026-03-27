//Player.cpp

#include "Player.h"
#include "Skill.h"
#include "Slash.h"
#include <iostream>
#include <vector>

// 플레이어 생성자 설정
Player::Player(const std::string& name)
    : name_(name), job_("용사"),
    maxLevel_(10),// 최대 레벨
    level_(1),         // 현재 레벨
    maxHp_(300),  // 최대 HP
    hp_(300),         // 현재 HP
    maxMp_(100),  // 최대 MP
    mp_(100),        // 현재 MP
    attack_(40),     // 공격력
    def_(20),          // 방어력
    maxExp_(100), // 최대 Exp
    exp_(0),      // 현재 Exp
    gold_(100) {} //현재 골드

std::string Player::GetName() const {return name_;}
std::string Player::GetJob() const { return job_; }
int Player::GetLevel() const{return level_;}
int Player::GetHP() const { return hp_;}
int Player::GetAttack() const {return attack_;}
int Player::GetDefense() const { return def_; }
int Player::GetExp() const {return exp_;}
int Player::GetMaxLevel() const { return maxLevel_; }
int Player::GetMaxHP() const { return maxHp_; }
int Player::GetMaxMP() const { return maxMp_; }
int Player::GetMaxExp() const { return maxExp_; }
int Player::GetMP() const { return mp_; }
int Player::GetGold() const { return gold_; }

void Player::SetName(std::string name) {name_ = name;}
void Player::SetJob(std::string job) {job_ = job;}
void Player::SetLevel(int level) {level_ = level;}
void Player::SetHP(int hp) {hp_ = hp;}
void Player::SetAttack(int attack) {attack_ = attack;}
void Player::SetDefense(int def) {def_ = def; }
void Player::gainGold(int G) { gold_ += G; } //골드 얻을때
void Player::gainExp(int exp) {exp_ += exp; } //경험치 얻을때


void Player::Heal(int hp) { //hp가 채워질때 (포션을 먹거나, 특별한 이벤트 등등..)
    hp_ += hp;
    if (hp_ >= maxHp_) {
        hp_ = maxHp_;
    }
}

void Player::UseMp(int mp) { //마나를 사용할때
    mp_ -= mp;
    if (mp_ < 0)
    {
        std::cout << "마나가 부족합니다!" << std::endl;
        mp_ += mp;
    }
}

void Player::loseGold(int G) {
    gold_ -= G;
    if (gold_ <= G) {
        gold_ = 0;
    }
}

void Player::Levelup() { // 레벨업
    while (exp_ >= maxExp_) { // 남은 경험치가 다음 최대 경험치를 넘으면 레벨업 반복
        if (level_ >= maxLevel_) {
            std::cout << "레벨이 최대입니다!" << std::endl;
            exp_ = 0;
            return;
        }
        level_ += 1;
        exp_ -= maxExp_; // maxExp를 초과할경우 현재 exp로 남은 값 넣어줌
        maxExp_ += 30;

        maxHp_ += 30;
        hp_ = maxHp_; // 현재 최대 HP만큼 100퍼센트 회복

        maxMp_ += 20;
        mp_ = maxMp_; // 현재 최대 MP만큼 100퍼센트 회복

        attack_ += 10;
        def_ += 5;

        if (level_ == 5)
        {
            learnSkill(new Slash());
            std::cout << "스킬을 획득했습니다" << std::endl;
        }
    }
}

Player::~Player()
{
    for (Skill* s : skillList)
    {
        delete s; 
    }
    skillList.clear();
}

