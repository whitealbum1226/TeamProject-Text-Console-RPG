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
