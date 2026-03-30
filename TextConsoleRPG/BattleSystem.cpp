// BattleSystem.cpp
#include "BattleSystem.h"
#include "Player.h"
#include "Monster/Monster.h"
#include "Monster/Slime.h"
#include "Monster/Goblin.h"

// ★ 스킬 관련 파일은 구현 전까지 완전히 주석 처리!
// #include "Skill.h"
// #include "Slash.h"

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

// ★ 괄호가 꼬여있던 문제의 함수를 깔끔하게 수정했습니다.
void BattleSystem::NextTurn()
{
    int choice;
    while (true)
    {
        std::cout << "\n1. 공격 / 2. 인벤토리 / 3. 스킬 / " << std::endl;
        std::cout << "선택: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            return;
        case 2:
            // 인벤토리 화면
            continue;
        case 3:
            std::cout << "아직 스킬 기능이 구현되지 않았습니다!\n";
            continue;
        default:
            std::cout << "잘못된 입력입니다." << std::endl;
            continue;
        }
    }
}

void BattleSystem::PlayerWin()
{
    int ShopSelect;
    int GoldRandom = (rand() % 11) + 20; // 20~30 골드 랜덤

    player->gainExp(50); // 경험치 50 증가
    player->gainGold(GoldRandom);
    player->Levelup();

    std::cout << "\n축하합니다! 전투에서 승리했습니다." << std::endl;
    std::cout << "얻은 경험치: 50 | 얻은 골드: " << GoldRandom << std::endl;
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

    if (MonsterRandom < 50)
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
        int AttackRandom = rand() % 100;

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