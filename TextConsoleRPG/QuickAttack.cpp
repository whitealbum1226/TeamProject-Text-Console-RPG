#include "QuickAttack.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>

bool QuickAttack::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume)
    {
        p.UseMp(mpConsume);

        p.SetQuickAttack(true); // 선공 맴버 변수 ture

        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}

void QuickAttack::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 마나를 사용해 적보다 빠르게 움직여 먼저 공격한다" << std::endl;
    std::cout << "         스킬을 사용하는 턴에 반드시 선제공격을 한다." << std::endl;
    std::cout << "========================================" << std::endl;
}
