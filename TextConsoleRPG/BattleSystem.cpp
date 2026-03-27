#include "BattleSystem.h"
#include "Player.h"
#include "Monster/Monster.h"
#include "Monster/Slime.h"
#include "Monster/Goblin.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

BattleSystem::BattleSystem(Player* p, Monster* m) : player(p), monster(m) {}

void BattleSystem::BattleReady()
{
    if (monster != nullptr)
    {
        std::cout << monster->GetName() << "이 나타났습니다!" << std::endl;
    }
}

void BattleSystem::PlayerWin()
{
    int ShopSelect;

    player->gainExp(50); // 경험치 50 증가
    std::cout << "상점에 진입 하시겠습니까. (예.1)";
    std::cin >> ShopSelect;

        if (ShopSelect == 1)
        {
            // 상점 함수 구현
        }
        else
        {
            std::cout << "다시 모험을 떠납니다." << std::endl;
        }

}


void BattleSystem::PlayerAttack()
{
    std::cout << player->GetName() << "의 " << turn << "번째 턴" << std::endl;
    monster->TakeDamage(player->GetAttack());
}

void BattleSystem::MonsterAttack() {
    std::cout << monster->GetName() << "의 " << turn << "번째 턴" << std::endl;
    player->TakeDamage(monster->GetAttack());
}
void BattleSystem::BattleStart()
{
    this->turn = 1; // 전투 시작 시 턴 1로 설정
    int MonsterRandom = rand() % 100; // 몬스터 출현 확률 0~99 난수

    if (MonsterRandom < 50) // 임시로 50%로 구현 이후 특정 조건에 새로운 몬스터 출현하도록 구현
    {
        monster = new Slime(10); // 임시로 레벨 넣었습니다
    }
    else if (MonsterRandom < 100)
    {
        monster = new Goblin(15);
    }

    BattleReady(); // 몬스터 생성 후 정보 출력

    while (player->GetHP() > 0 && monster->GetHP() > 0)
    {
        int AttackRandom = rand() % 100; // 플레이어 몬스터 공격 순서 랜덤 (이후 특정 조건으로 확률 변경 가능)

        if (AttackRandom < 50) // 플레이어 선공
        {
            PlayerAttack();
            if (monster->GetHP() <= 0)
            {
                std::cout << monster->GetName() << "을(를) 처치했습니다." << std::endl;
                PlayerWin();
                break; // 공격 대상의 체력이 0이면 반복문 탈출
            }

            MonsterAttack();
            if (player->GetHP() <= 0)
            {
                std::cout << player->GetName() << "이(가) 전투에서 패배합니다." << std::endl;


                break;
            }
        }
        else // 몬스터 선공
        {
            MonsterAttack();
            if (player->GetHP() <= 0)
            {
                std::cout << player->GetName() << "이(가) 전투에서 패배합니다." << std::endl;


                break;
            }

            PlayerAttack();
            if (monster->GetHP() <= 0)
            {
                std::cout << monster->GetName() << "을(를) 처치했습니다." << std::endl;
                PlayerWin();
                break; 
            }
        }
  
        turn++; // 턴 증가
    }

    if (monster != nullptr) // 몬스터 누수 방지
    {
        delete monster;
        monster = nullptr; 
    }
}
