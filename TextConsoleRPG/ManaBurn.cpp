#include "ManaBurn.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>

bool ManaBurn::useSkill(Player& p, Monster& m)
{
    int CurruntMp = p.GetMP(); // 스킬 재사용 시 마나 소모량을 초기화 하기 위한 변수 선언

    if (CurruntMp > 0)
    {
        int damage = p.GetMP() * 3; //데미지 로직 (현재 마나 *3)
         
        p.UseMp(CurruntMp); // 현재 마나 전체 소모
        m.TakeDamage(damage);
        std::cout << "\n" << name << "을 사용합니다 " << std::endl;
        std::cout << "MP: " << CurruntMp << " → " << "0" << std::endl;

        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}

void ManaBurn::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 마나를 모두 소비하여 마나 폭발을 일으킨다." << std::endl;
    std::cout << "          플레이어의 MP를 모두 사용하고 사용한 MP의 3배만큼 데미지를 입힌다." << std::endl;
    std::cout << "========================================" << std::endl;
}
