#include "Boom.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>

bool Boom::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume && p.GetHP() > 30)
    {
        p.UseMp(mpConsume);

        p.TakeDamage(30); // 플레이어도 폭발 피해를 받음
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
