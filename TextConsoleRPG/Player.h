//Player.h

#pragma once
#include <string>

class Player
{
public:
    Player(const std::string& name);

    std::string GetName() const;
    std::string GetJob() const;
    int GetLevel() const;
    int GetHP() const;
    int GetAttack() const;
    int GetDeffence() const;
    int GetExp() const;
    int GetMaxExp() const;
    int GetMaxLevel() const;
    int GetMaxHP() const;
    int GetMaxMP() const;
    int GetMP() const;

    void SetName(std::string name);
    void SetJob(std::string job);
    void SetLevel(int level);
    void SetHP(int hp);
    void SetDefence(int def);
    void SetAttack(int attack);
    void gainExp(int exp);
    bool IsDead() const;
    void TakeDamage(int damage);
    void Levelup();
    
private:
    std::string name_;
    std::string job_;
    int maxLevel_;
    int level_;
    int hp_;
    int maxHp_;
    int mp_;
    int maxMp_;
    int attack_;
    int exp_;
    int maxExp_;
    int def_;
};
