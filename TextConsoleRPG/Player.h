//Player.h

#pragma once
#include <string>
#pragma once

class Player
{
public:
    Player(const std::string& name);

    std::string GetName() const;
    std::string GetJob() const;
    int GetLevel() const;
    int GetHP() const;
    int GetAttack() const;
    int GetDefense() const;
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
    void SetDefense(int def);
    void SetAttack(int attack);
    void gainExp(int exp);
    void Levelup();
    void PrintStatus();
    void gainGold(int G);
    void loseGold(int G);

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
    int gold_;
};
