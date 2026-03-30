#include "Blood.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>

bool Blood::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume)
    {
        p.UseMp(mpConsume);

        std::cout << name << "을 사용합니다 " << std::endl;

        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}

void Blood::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 적에게 출혈을 입힙니다." << std::endl;
    std::cout << "          3턴동안 몬스터가 플레이어를 공격 후 30에 데미지를 입습니다." << std::endl;
    std::cout << "========================================" << std::endl;
}
