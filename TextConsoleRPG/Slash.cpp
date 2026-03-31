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

        std::cout << "\n" << name << "을 사용합니다 " << std::endl;
        std::cout << "MP: " << p.GetMP() + mpConsume << " → " << p.GetMP() << std::endl;

        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}

void Slash::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 적에게 검귀를 날린다." << std::endl;
    std::cout << "          플레이어 공격력의 2배만큼 데미지를 준다." << std::endl;
    std::cout << "========================================" << std::endl;
}
