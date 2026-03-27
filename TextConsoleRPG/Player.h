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
    int GetExp() const;

    void SetName(std::string name);
    void SetJob(std::string job);
    void SetLevel(int level);
    void SetHP(int hp);
    void SetAttack(int attack);
    void SetExp(int exp);

private:
    std::string name_;
    std::string job_;
    int level_;
    int hp_;
    int attack_;
    int exp_;
};