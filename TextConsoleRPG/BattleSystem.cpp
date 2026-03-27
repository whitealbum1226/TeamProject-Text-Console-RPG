#include "BattleSystem.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

BattleSystem::BattleSystem(Player* p, Monster* m) : player(p), monster(m) {}

void BattleSystem::BattleReady()
{
    if (monster != nullptr)
    {
        std::cout << monster->GetName() << "이 나타났습니다!" << std::endl;
    }
}

void BattleSystem::BattleStart()
{
    while (player->GetHP() > 0 && monster->GetHP() > 0)
    {
        std::cout << player->GetName() << "의 " << turn << "번째 턴" << std::endl;
        monster->TakeDamage(player->GetAttack()); // 플레이어 공격력 만큼 몬스터 체력 깍음
        if (monster->GetHP() <= 0)
        {
            std::cout << monster->GetName() << "을(를) 처치했습니다." << std::endl;
            break; // 공격 대상의 체력이 0이면 반복문 탈출
        }

        std::cout << monster->GetName() << "의 " << turn << "번째 턴" << std::endl;
        player->TakeDamage(monster->GetAttack());
        if (player->GetHP() <= 0)
        {
            std::cout << player->GetName() << "이(가) 전투에서 패배합니다." << std::endl;
            break;
        }
        turn++;
    }
}
