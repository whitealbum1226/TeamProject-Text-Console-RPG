#pragma once

#include <iostream>
#include "Monster/Monster.h"
#include "Player.h"
#include <string>
#include <vector>

class Player;
class Monster;

class Skill
{
protected:
    std::string name;
    int mpConsume;

public:
    Skill(std::string n, int m) : name(n), mpConsume(m) {}

    virtual ~Skill() {}

    virtual bool useSkill(Player& p, Monster& m) = 0;

    const std::string& getName() const { return name; }
    int getMpConsume() const { return mpConsume; }
};
