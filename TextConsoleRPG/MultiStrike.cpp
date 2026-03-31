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

        int attackCount = (rand() % 3) + 2; // 2 ~ 4번 랜덤 공격

        std::cout << "\n" << name << "을 사용합니다 " << std::endl;
        std::cout << "MP: " << p.GetMP() + mpConsume << " → " << p.GetMP() << std::endl;

        for (int i = 1; i <= attackCount; i++)
        {
            std::cout << i << "번째 공격! ";
            m.TakeDamage(p.GetAttack());
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

void MultiStrike::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 마나를 소비하여 적을 여러 번 공격한다" << std::endl;
    std::cout << "          같은 확률로 적을 최소 2번, 최대 4번 공격한다 " << std::endl;
    std::cout << "========================================" << std::endl;
}
