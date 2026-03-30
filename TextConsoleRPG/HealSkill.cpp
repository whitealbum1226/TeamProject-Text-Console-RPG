#include "HealSkill.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>

bool HealSkill::useSkill(Player& p, Monster& m)
{
    if (p.GetHP() >= p.GetMaxHP())
    {
        std::cout << "이미 최대 체력입니다." << std::endl;
        return false;
    }

    if (p.GetMP() < mpConsume)
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
    else
    {
        p.UseMp(mpConsume);

        int healAmount = 50;

        // 오버힐 방지 계산
        if (p.GetHP() + healAmount > p.GetMaxHP())
        {
            healAmount = p.GetMaxHP() - p.GetHP();
        }

        p.Heal(healAmount);
        std::cout << name << "을(를) 사용합니다! (+" << healAmount << " HP)" << std::endl;
    }

    return true;
}
