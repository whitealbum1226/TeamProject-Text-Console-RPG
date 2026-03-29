#pragma once
#include "Skill.h"

class Slash : public Skill {
public:
    bool useSkill(Player& p, Monster& m) override; 
};
