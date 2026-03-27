// Monster.h

#pragma once
#include <string>

class Monster
{
public:
    Monster(const std::string& name, int playerLevel);

    virtual ~Monster() {};
    virtual void TakeDamage(int takeDamage);
    bool IsDead() const;

    std::string GetName() const;
    int GetHP() const;
    int GetMaxHP() const;
    int GetAttack() const;
    int GetDefense() const;

    void SetName(std::string name);
    void SetHP(int hp);
    void SetAttack(int attack);
    void SetDefense(int defense);

protected:
    std::string name_;
    int hp_;
    int maxHp_;
    int attack_;
    int defense_;
};
