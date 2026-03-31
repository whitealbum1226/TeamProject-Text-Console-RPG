#include "Roulette.h"      
#include "Player.h"     
#include "Monster/Monster.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

bool Roulette::useSkill(Player& p, Monster& m)
{
    if (p.GetMP() >= mpConsume)
    {
        p.UseMp(mpConsume);

        int event = rand() % 100; // 0 ~ 99

        if (event < 40) // 40% 기본 공격
        {
            int damage = p.GetAttack(); 
            m.TakeDamage(damage);
        }
        else if (event < 60)
        {
            int damage = p.GetAttack() * 2 ; // 20% 2배 데미지 공격
            m.TakeDamage(damage);
        }
        else if (event < 70) // 10% 체력 전체 회복
        {
            p.Heal(p.GetMaxHP());
        }
        else if (event < 80) // 10% 마나 전체 회복
        {
            p.RecoverMP(p.GetMaxMP());
        }
        else if (event < 88) // 8% 플레이어 현재 체력이 반으로 깎임
        {
            int selfDamage = p.GetHP() / 2;
            p.TakeDamage(selfDamage);
        }
        else if (event < 96) // 8% 플레이어 현재 체력이 반으로 깎임
        {
            int selfDamage = m.GetHP() / 2;
            m.TakeDamage(selfDamage);
        }
        else if(event < 98) // 2% 확률로 플레이어 즉사
        {
            int selfDamage = p.GetHP();
            p.TakeDamage(selfDamage);
        }
        else // 2% 확률로 몬스터 즉사
        {
            int selfDamage = m.GetHP();
            m.TakeDamage(selfDamage);
        }


        std::cout << "\n" << name << "을 사용합니다 " << std::endl;
        std::cout << "MP: " << p.GetMP() + mpConsume << "→" << p.GetMP() << std::endl;

        return true;
    }
    else
    {
        std::cout << "MP가 부족합니다." << std::endl;
        return false;
    }
}

void Roulette::ShowDetail()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << " [스킬명] " << name << " (소모 MP: " << mpConsume << ")" << std::endl;
    std::cout << " [설  명] 운명의 룰렛을 돌려 다양한 효과를 발동한다." << std::endl;
    std::cout << "          1. (40% 확률) 일반 공격 2. (20% 확률) 2배 데미지 공격 3. (10% 확률) 플레이어 HP 전체 회복 4. (10% 확률) 플레이어 MP 전체 회복" << std::endl;
    std::cout << "          5. (8% 확률) 플레이어 현재 체력 절반 감소 6. (8% 확률) 적 현재 체력 50% 감소 7. (2% 확률) 플레이어 즉사 8. (2% 확률) 적 즉사" << std::endl;
    std::cout << "========================================" << std::endl;
}
