#include "Slash.h"      // 내 헤더
#include "Player.h"     // Player 기능을 쓰기 위해
#include "Monster/Monster.h" // Monster 기능을 쓰기 위해 (경로 주의)
#include <iostream>

bool Slash::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume)
    {
        p.UseMp(mpConsume);

        int damage = p.GetAttack() * 2; //데미지 로직
        m.TakeDamage(damage);

        // 3. 결과 출력
        std::cout << name << "을 사용합니다 " << std::endl;

        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}
