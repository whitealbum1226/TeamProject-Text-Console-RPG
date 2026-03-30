// Player.cpp
#include "Player.h"
#include <iostream>

// ★ 주의: 스킬 파일이 준비되었다면 아래 두 줄의 주석을 푸세요!
// #include "Skill.h"
// #include "Slash.h"

Player::Player(const std::string& name)
    : name_(name), job_("용사"),
    maxLevel_(10), level_(1),
    maxHp_(300), hp_(300),
    maxMp_(100), mp_(100),
    attack_(40), def_(20),
    maxExp_(100), exp_(0), gold_(100) {
}

Player::~Player()
{
    // ★ 주의: 스킬 클래스가 구현되기 전까지는 이 부분을 주석 처리해 둡니다.
    /*
    for (Skill* s : skillList) {
        delete s;
    }
    skillList.clear();
    */
}

std::string Player::GetName() const { return name_; }
std::string Player::GetJob() const { return job_; }
int Player::GetLevel() const { return level_; }
int Player::GetHP() const { return hp_; }
int Player::GetAttack() const { return attack_; }
int Player::GetDefense() const { return def_; }
int Player::GetExp() const { return exp_; }
int Player::GetMaxLevel() const { return maxLevel_; }
int Player::GetMaxHP() const { return maxHp_; }
int Player::GetMaxMP() const { return maxMp_; }
int Player::GetMaxExp() const { return maxExp_; }
int Player::GetMP() const { return mp_; }
int Player::GetGold() const { return gold_; }

void Player::SetName(std::string name) { name_ = name; }
void Player::SetJob(std::string job) { job_ = job; }
void Player::SetLevel(int level) { level_ = level; }
void Player::SetHP(int hp) { hp_ = hp; }
void Player::SetAttack(int attack) { attack_ = attack; }
void Player::SetDefense(int def) { def_ = def; }

void Player::gainGold(int G) { gold_ += G; }
void Player::gainExp(int exp) { exp_ += exp; }

void Player::Heal(int hp) {
    hp_ += hp;
    if (hp_ >= maxHp_) {
        hp_ = maxHp_;
    }
}

void Player::RecoverMP(int amount) {
    mp_ += amount;
    if (mp_ > maxMp_) mp_ = maxMp_;
}

void Player::UseMp(int mp) {
    mp_ -= mp;
    if (mp_ < 0) {
        std::cout << "마나가 부족합니다!" << std::endl;
        mp_ += mp; // 마나가 부족하면 다시 원상복구
    }
}

void Player::loseGold(int G) {
    gold_ -= G;
    if (gold_ < 0) {
        gold_ = 0;
    }
}

bool Player::IsAlive() const {
    return hp_ > 0;
}

void Player::TakeDamage(int takeDamage) {
    if (takeDamage <= 0) {
        takeDamage = 1; // 최소 데미지 1
    }
    hp_ -= takeDamage;

    if (hp_ < 0) {
        hp_ = 0;
    }
}

void Player::Levelup() {
    while (exp_ >= maxExp_) {
        if (level_ >= maxLevel_) {
            std::cout << "레벨이 최대입니다!" << std::endl;
            exp_ = 0;
            return;
        }
        level_ += 1;
        exp_ -= maxExp_;
        maxExp_ += 30;

        maxHp_ += 30;
        hp_ = maxHp_;

        maxMp_ += 20;
        mp_ = maxMp_;

        attack_ += 10;
        def_ += 5;

        if (level_ == 5) {
            // ★ 주의: 스킬 기능이 완성되면 아래 두 줄의 주석을 푸세요!
            // learnSkill(new Slash());
            // std::cout << "스킬을 획득했습니다" << std::endl;
        }
    }
}

void Player::PrintStatus() {
    std::cout << "이름: " << name_ << "\n";
    std::cout << "직업: " << job_ << "\n";
    std::cout << "레벨: " << level_ << " / 최대 레벨: " << maxLevel_ << "\n";
    std::cout << "HP: " << hp_ << " / 최대 HP: " << maxHp_ << "\n";
    std::cout << "MP: " << mp_ << " / 최대 MP: " << maxMp_ << "\n";
    std::cout << "공격력: " << attack_ << "\n";
    std::cout << "방어력: " << def_ << "\n";
    std::cout << "EXP: " << exp_ << " / 최대 EXP: " << maxExp_ << "\n";
    std::cout << "골드: " << gold_ << "\n";
}

