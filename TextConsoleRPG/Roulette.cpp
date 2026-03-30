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


        std::cout << name << "을 사용합니다 " << std::endl;

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

}
