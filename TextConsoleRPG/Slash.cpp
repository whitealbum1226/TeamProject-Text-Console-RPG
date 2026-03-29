#include "Slash.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>

bool Slash::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume)
    {
        p.UseMp(mpConsume);

        int damage = p.GetAttack() * 2; //데미지 로직
        m.TakeDamage(damage);

        std::cout << name << "을 사용합니다 " << std::endl;

        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}
