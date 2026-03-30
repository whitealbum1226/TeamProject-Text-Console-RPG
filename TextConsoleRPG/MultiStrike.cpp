#include "MultiStrike.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

bool MultiStrike::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume)
    {
        p.UseMp(mpConsume);

        int attackCount = (rand() % 4) + 2; // 2 ~ 5번 랜덤 공격

        std::cout << name << "을 사용합니다 " << std::endl;

        for (int i = 1; i <= attackCount; i++)
        {
            int damage = p.GetAttack();
            m.TakeDamage(damage);
        }

        std::cout << attackCount << "번 공격했습니다." << std::endl;
        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}
