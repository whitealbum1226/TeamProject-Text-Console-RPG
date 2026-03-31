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
        std::cout << "\n" << name << "을(를) 사용합니다! (+" << healAmount << " HP)" << std::endl;
        std::cout << "MP: " << p.GetMP() + mpConsume << "→" << p.GetMP() << std::endl;
    }

    return true;
}

void HealSkill::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 마나를 소비하여 자신을 치료합니다." << std::endl;
    std::cout << "          플레이어의 체력을 50 회복합니다." << std::endl;
    std::cout << "========================================" << std::endl;
}
