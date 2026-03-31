#include "BattleSystem.h"
#include "Player.h"
#include "Monster/Monster.h"
#include "Monster/Slime.h"
#include "Monster/Goblin.h"
#include "Skill.h"
#include "Slash.h"
#include "Boom.h"
#include "HealSkill.h"
#include "MultiStrike.h"
#include "Blood.h"
#include "ManaBurn.h"
#include "Roulette.h"
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
            // BattleSystem.cpp 내 NextTurn 함수 중 일부 수정
        case 3:
        {
            auto& skills = player->getSkillList();
            if (skills.empty()) {
                std::cout << "배운 스킬이 없습니다!" << std::endl;
                continue;
            }

            while (true) {
                std::cout << "\n[ 스킬 메뉴 ]" << std::endl;
                std::cout << "1. 스킬 사용 / 2. 스킬 상세 설명 / 0. 뒤로 가기" << std::endl;
                std::cout << "선택: ";
                int skillMenu;
                std::cin >> skillMenu;

                if (skillMenu == 0) break; // 스킬 메뉴 탈출 -> 1.공격/2.인벤토리 메뉴로

                if (skillMenu == 1) { // 스킬 사용 
                    std::cout << "\n[ 사용 가능한 스킬 ]" << std::endl;
                    for (int i = 0; i < (int)skills.size(); ++i)
                    {
                        std::cout << i + 1 << ". " << skills[i]->getName() << " (MP: " << skills[i]->getMpConsume() << ")" << std::endl;
                    }

                    int useChoice;
                    std::cout << "번호 입력 (0.취소): ";
                    std::cin >> useChoice;

                    if (useChoice <= 0 || useChoice > (int)skills.size()) continue;

                    Skill* selectedSkill = skills[useChoice - 1];

                    if (player->GetMP() >= selectedSkill->getMpConsume())
                    {

                        if (selectedSkill->useSkill(*player, *monster)) {
                            player->UseMp(selectedSkill->getMpConsume());
                            return;
                        }
                    }
                    else
                    {
                        std::cout << "마나가 부족합니다! (현재 MP: " << player->GetMP() << ")" << std::endl;
                    }
                    continue;
                }
                else if (skillMenu == 2)
                {
                    while (true)
                    {
                        std::cout << "\n========================================" << std::endl;
                        std::cout << "            [   스킬 도감   ]          " << std::endl;
                        std::cout << "========================================" << std::endl;

                        for (int i = 0; i < (int)skills.size(); ++i) {
                            std::cout << i + 1 << ". " << skills[i]->getName() << std::endl;
                        }
                        std::cout << "0. 돌아가기" << std::endl;
                        std::cout << "선택: ";

                        int dictChoice;
                        std::cin >> dictChoice;

                        if (dictChoice == 0) break; // 스킬 메뉴(사용/설명)로 이동

                        if (dictChoice > 0 && dictChoice <= (int)skills.size()) {
                            // 네가 Skill.h에 만든 ShowDetail() 호출
                            skills[dictChoice - 1]->ShowDetail();
                        }
                        else
                        {
                            std::cout << "잘못된 번호입니다." << std::endl;
                        }
                    }
                }
            }
            continue;
        }
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
    std::cout << "\n" << player->GetName() << "의 " << turn << "번째 턴" << std::endl;
    monster->TakeDamage(player->GetAttack());

    std::cout << player->GetAttack() << "를 입힙니다" << std::endl;
    std::cout << monster->GetName() << "의 HP : " << monster->GetHP() << std::endl;
}

void BattleSystem::MonsterAttack() {
    std::cout << "\n" << monster->GetName() << "의 " << turn << "번째 턴" << std::endl;
    player->TakeDamage(monster->GetAttack());
    if (blood != nullptr && blood->GetBloodCount() > 0) // 출혈 스킬이 있고 카운트가 0보다 클 경우
    {
        monster->TakeDamage(blood->GetBloodDamage());
        blood->SetBloodCount(blood->GetBloodCount() - 1);
    }

    std::cout << monster->GetAttack() << "만큼의 데미지를 입었습니다" << std::endl;
    std::cout << "플레이어의 HP: " << player->GetHP() << std::endl;
}
void BattleSystem::BattleStart()
{
    this->turn = 1; // 전투 시작 시 턴 1로 설정
    int MonsterRandom = rand() % 100; // 몬스터 출현 확률 0~99 난수

    this->blood = nullptr; // 지속 피해
    auto& skills = player->getSkillList();
    for (int i = 0; i < (int)skills.size(); ++i) // 출혈 스킬을 배웠을 경우 포인터에 스킬을 넣음
    {
        if (skills[i]->getName() == "출혈")
        {
            blood = (Blood*)skills[i];
            break; 
        }
    }

    if (MonsterRandom < 50) // 임시로 50%로 구현 이후 특정 조건에 새로운 몬스터 출현하도록 구현
    {
        monster = new Slime(5); // 임시로 레벨 넣었습니다
    }
    else if (MonsterRandom < 100)
    {
        monster = new Goblin(8);
    }

    BattleReady(); // 몬스터 생성 후 정보 출력

    while (player->GetHP() > 0 && monster->GetHP() > 0)
    {
        NextTurn();

        int AttackRandom = rand() % 100; // 플레이어 몬스터 공격 순서 랜덤 (이후 특정 조건으로 확률 변경 가능)

        if (AttackRandom < 50 || player->GetQuickAttack() == true) // 플레이어 선공 (신속 스킬 사용 시 선공 구현)
        {
            player->SetQuickAttack(false);
            std::cout << player->GetName() << "의 선공."  << std::endl;
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
                std::cout << "\n" << player->GetName() << "이(가) 전투에서 패배합니다." << std::endl;
                break;
            }
        }
        else // 몬스터 선공
        {
            std::cout << monster->GetName() << "의 선공." << std::endl;

            MonsterAttack();
            if (player->GetHP() <= 0)
            {
                std::cout << "\n" << player->GetName() << "이(가) 전투에서 패배합니다." << std::endl;
                break;
            }
            if (monster->GetHP() <= 0) // 몬스터가 출혈로 죽었을 경우를 대비
            {
                std::cout << "\n" << monster->GetName() << "을(를) 처치했습니다." << std::endl;
                PlayerWin();
                break;
            }

            PlayerAttack();
            if (monster->GetHP() <= 0)
            {
                std::cout << "\n" << monster->GetName() << "을(를) 처치했습니다." << std::endl;
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
