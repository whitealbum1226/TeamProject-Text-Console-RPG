#include "BattleSystem.h"
#include "Player.h"
#include "Monster/Monster.h"
#include "Monster/Slime.h"
#include "Monster/Goblin.h"
#include "Inventory.h"
#include "GameLog.h"
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

BattleSystem::BattleSystem(Player* p, Monster* m, GameLog* lg, Inventory* inv)
    : player(p), monster(m), logSystem(lg), inventory(inv), blood(nullptr), turn(1) {
}

void BattleSystem::BattleReady()
{
    if (monster != nullptr)
    {
        logSystem->AddLog(monster->GetName() + "이(가) 나타났습니다!");
    }
}
bool BattleSystem::ExecuteSkill(Skill* selectedSkill)
{
    if (player->GetMP() >= selectedSkill->getMpConsume())
    {
        logSystem->ClearScreen();
        logSystem->AddLog(player->GetName() + "의 기술: [" + selectedSkill->getName() + "]!");
        int oldHP = monster->GetHP();

        if (selectedSkill->useSkill(*player, *monster))
        {
            std::string sName = selectedSkill->getName();
            if (sName == "슬래시") logSystem->DrawSkillSlash();
            else if (sName == "신속") logSystem->DrawSkillQuick();
            else if (sName == "회복") logSystem->DrawSkillHeal();
            else if (sName == "출혈") logSystem->DrawSkillBlood();
            else if (sName == "폭발") logSystem->DrawSkillBoom();
            else if (sName == "마나 익스플로전") logSystem->DrawSkillManaBurn();
            else if (sName == "운명의 룰렛") logSystem->DrawSkillRoulette();
            else if (sName == "연속 공격") logSystem->DrawSkillMultiStrike();

            std::cout << "\n[ ENTER 키를 눌러 결과를 확인하세요 ]";
            std::cin.ignore(1000, '\n');
            std::cin.get();

            int damageDealt = oldHP - monster->GetHP();
            if (damageDealt > 0) {
                logSystem->AddLog(monster->GetName() + "에게 " + std::to_string(damageDealt) + "의 피해!");
            }
            player->UseMp(selectedSkill->getMpConsume());

            logSystem->DrawBattleScreen(*player, *monster);
            std::cout << "\n(엔터를 누르면 전투가 진행됩니다...)";
            std::cin.get();
            return true;
        }
    }
    else
    {
        logSystem->AddLog("마나가 부족합니다!");
        std::cout << "현재 MP가 부족하여 기술을 쓸 수 없습니다." << std::endl;
        std::cin.ignore(1000, '\n');
        std::cin.get();
    }
    return false;
}


bool BattleSystem::NextTurn()
{
    int choice;
    while (true)
    {
        logSystem->DrawBattleScreen(*player, *monster);
        std::cout << "선택: ";
        if (!(std::cin >> choice))
        { 
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1: //  일반 공격
            std::cin.ignore(1000, '\n');
            return true;

        case 2: // 인벤토리
        {
            logSystem->DrawInventoryScreen(*inventory);

            int itemChoice;
            std::cout << "사용할 아이템 번호 (0.취소): ";
            std::cin >> itemChoice;

            if (itemChoice <= 0) continue;

            InventoryItemData itemData = inventory->GetItem(itemChoice - 1);

            if (itemData.name == "") {
                std::cout << "해당 칸에 아이템이 없습니다!" << std::endl;
                continue;
            }

            inventory->UseItem(itemChoice - 1, *player);
            logSystem->AddLog(player->GetName() + "이(가) [" + itemData.name + "]을(를) 사용했습니다.");

            std::cout << "\n(엔터를 누르면 계속합니다...)";
            std::cin.ignore(1000, '\n');
            std::cin.get();

            return false;
        }

        case 3: // 스킬 메뉴 
        {
            auto& skills = player->getSkillList();
            if (skills.empty())
            {
                std::cout << "배운 스킬이 없습니다!" << std::endl;
                continue;
            }

            bool skillUsed = false; // 스킬 사용 여부 체크
            while (true)
            {
                std::cout << "\n[ 스킬 메뉴 ]" << std::endl;
                std::cout << "1. 스킬 사용 / 2. 스킬 상세 설명 / 0. 뒤로 가기" << std::endl;
                std::cout << "선택: ";
                int skillMenu;
                std::cin >> skillMenu;

                if (skillMenu == 0) break; // 스킬 메뉴 나가기 

                if (skillMenu == 1)
                { 
                    std::cout << "\n[ 사용 가능한 스킬 ]" << std::endl;
                    for (int i = 0; i < (int)skills.size(); ++i) {
                        std::cout << i + 1 << ". " << skills[i]->getName() << " (MP: " << skills[i]->getMpConsume() << ")" << std::endl;
                    }

                    int useChoice;
                    std::cout << "번호 입력 (0.취소): ";
                    std::cin >> useChoice;

                    if (useChoice <= 0 || useChoice > (int)skills.size()) continue;

                    if (ExecuteSkill(skills[useChoice - 1]))
                    {
                        return false; 
                    }
                }
                else if (skillMenu == 2)
                { 
                    std::cout << "\n========== [ 스킬 도감 ] ==========" << std::endl;
                    for (int i = 0; i < (int)skills.size(); ++i) {
                        std::cout << i + 1 << ". " << skills[i]->getName() << std::endl;
                    }
                    std::cout << "0. 돌아가기\n선택: ";

                    int dictChoice;
                    std::cin >> dictChoice;
                    if (dictChoice > 0 && dictChoice <= (int)skills.size())
                    {
                        logSystem->DrawSkillDetail(skills[dictChoice - 1]);

                        int detailChoice;
                        std::cin >> detailChoice;
                        if (detailChoice == 1) {
                            if (ExecuteSkill(skills[dictChoice - 1]))
                            {
                                return false; // 스킬 사용 성공 시 NextTurn 종료
                            }
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
    int GoldRandom = (rand() % 11) + 20;

    logSystem->RecordMonsterKill(monster->GetName());
    logSystem->AddLog(monster->GetName() + "을(를) 처치했습니다!");

    logSystem->DrawExpGoldGain(50, GoldRandom);

    player->gainExp(50);
    player->gainGold(GoldRandom);
    if (player->Levelup()) {
        logSystem->AddLog("★ LEVEL UP! ★");
    }

    std::cout << "\n상점에 진입 하시겠습니까? (1.예 / 0.아니오): ";
    int ShopSelect;
    std::cin >> ShopSelect;
    if (ShopSelect == 1) logSystem->DrawShopUI();
}

void BattleSystem::PlayerAttack()
{
    int damage = player->GetAttack();
    monster->TakeDamage(damage);

    logSystem->ClearScreen();
    logSystem->DrawAttackPunch();

    std::cout << "\n[ ENTER: 결과 확인 ]";
    std::cin.get();

    std::string battleMsg = player->GetName() + "의 공격! "
        + monster->GetName() + "에게 " + std::to_string(damage) + "의 피해!";
    logSystem->AddLog(battleMsg);

    if (monster->GetHP() <= 0) logSystem->AddLog(monster->GetName() + "이(가) 쓰러졌습니다!");

    logSystem->DrawBattleScreen(*player, *monster);

    std::cout << "\n"<< player->GetName() << "의 공격이 성공했습니다. (ENTER)";
    std::cin.get();
}

void BattleSystem::MonsterAttack()
{
    int mDamage = monster->GetAttack();
    player->TakeDamage(mDamage);

    if (blood != nullptr && blood->GetBloodCount() > 0)
    {
        int bDamage = blood->GetBloodDamage();
        monster->TakeDamage(bDamage);
        blood->SetBloodCount(blood->GetBloodCount() - 1);
        logSystem->AddLog( monster->GetName() + "이(가) 출혈로 " + std::to_string(bDamage) + "의 피해!");
    }

    logSystem->AddLog(monster->GetName() + "의 공격! " + std::to_string(mDamage) + "의 피해.");

    logSystem->DrawBattleScreen(*player, *monster);

    std::cout << "\n" << monster->GetName()  << "이 " << player->GetName() << "을 공격했습니다 (ENTER)";
    std::cin.get();
}

void BattleSystem::BattleStart()
{
    this->turn = 1;
    int MonsterRandom = rand() % 100;

    this->blood = nullptr;
    auto& skills = player->getSkillList();
    for (int i = 0; i < (int)skills.size(); ++i)
    {
        if (skills[i]->getName() == "출혈")
        {
            blood = (Blood*)skills[i];
            break;
        }
    }

    if (MonsterRandom < 50) monster = new Slime(5);
    else monster = new Goblin(8);

    logSystem->ClearScreen();
    BattleReady();

    while (player->GetHP() > 0 && monster->GetHP() > 0)
    {
        logSystem->AddLog("[" + std::to_string(turn) + "번째 턴]");

        bool isNormalAttack = NextTurn();
        int AttackRandom = rand() % 100;

        // 플레이어 신속 스킬 써을 경우
        if (player->GetQuickAttack() == true)
        {
            // 신속 플래그 초기화
            player->SetQuickAttack(false);

            // 스킬 사용 직후 '즉시' 공격 실행
            PlayerAttack();

            if (monster->GetHP() <= 0) {
                PlayerWin();
                break;
            }

            MonsterAttack();
        }
        else // 신속 사용하지 않은 일반적인 공격 처리
        {
            // 플레이어 선공 (확률 50%)
            if (AttackRandom < 50)
            {
                if (isNormalAttack) PlayerAttack();

                if (monster->GetHP() <= 0) {
                    PlayerWin();
                    break;
                }
                MonsterAttack();
            }
            // 몬스터 선공
            else
            {
                MonsterAttack();

                if (player->GetHP() <= 0) {
                    logSystem->AddLog(player->GetName() + "이(가) 패배했습니다...");
                    break;
                }

                if (isNormalAttack) PlayerAttack();

                if (monster->GetHP() <= 0) {
                    PlayerWin();
                    break;
                }
            }
        }

        turn++; //  턴 증가
    }

    if (monster != nullptr)
    {
        delete monster;
        monster = nullptr;
    }
}

