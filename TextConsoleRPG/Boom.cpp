#include "Boom.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>

bool Boom::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume && p.GetHP() > 30)
    {
        p.UseMp(mpConsume);

        p.TakeDamage(50); // 플레이어도 폭발 피해를 받음
        int damage = p.GetAttack() * 4; //데미지 로직
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

void Boom::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 마나를 소모하여 폭발을 일으킨다." << std::endl;
    std::cout << "          플레이어는 50의 데미지를 입고 몬스터에게 공격력 4배의 데미지를 줍니다." << std::endl;
    std::cout << "========================================" << std::endl;
}
