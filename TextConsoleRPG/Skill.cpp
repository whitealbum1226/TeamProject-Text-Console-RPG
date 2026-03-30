#pragma once
#include <string>

class Player;
class Monster;

class Skill
{
protected:
    std::string name;
    int mpConsume;

public:
    virtual ~Skill() {}

    virtual bool useSkill(Player& p, Monster& m) = 0;
};
