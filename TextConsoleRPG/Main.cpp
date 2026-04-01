// Main.cpp

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "Inventory.h"
#include "Store.h"
#include "BattleSystem.h"
#include "GameLog.h"

// 중복된 입력을 함수로!
void Next()
{
    std::cin.ignore(20, '\n');
    std::cin.get();
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameLog log;
    Player player("Player");
    Inventory inventory;
    Store store;

    int startChoice = log.ShowMainMenu();
    if (startChoice != 1)
    {
        std::cout << "게임을 종료합니다.\n";
        return 0;
    }

    log.SetupCharacter(&player);

    while (true)
    {
        if (!player.IsAlive())
        {
            log.DrawGameOver();
            break;
        }

        log.ClearScreen();
        std::cout << "==================================================\n";
        std::cout << "                    메인 메뉴\n";
        std::cout << "==================================================\n";
        std::cout << "1. 상태 보기\n";
        std::cout << "2. 전투 시작\n";
        std::cout << "3. 상점 입장\n";
        std::cout << "4. 인벤토리 확인\n";
        std::cout << "5. 아이템 사용\n";
        std::cout << "6. 토벌 현황 확인\n";
        std::cout << "0. 게임 종료\n";
        std::cout << "99. 시연용 치트키\n";
        std::cout << "선택 >> ";

        int menu;
        std::cin >> menu;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "잘못된 입력입니다.\n";
            continue;
        }

        switch (menu)
        {
        case 1:
        {
            log.DrawPlayerStatScreen(player);

            std::cout << "\n엔터키를 눌러주세요! >> ";
            Next();
            break;
        }

        case 2:
        {
            BattleSystem battle(&player, nullptr, &log, &inventory);
            battle.BattleStart();

            std::cout << "\n엔터키를 눌러주세요! >> ";
            Next();
            break;
        }

        case 3:
        {
            store.Open(player, inventory);
            break;
        }

        case 4:
        {
            log.DrawInventoryScreen(inventory);

            Next();
            break;
        }

        case 5:
        {
            if (inventory.GetItemCount() == 0)
            {
                std::cout << "인벤토리가 비어 있습니다.\n";

                std::cout << "엔터키를 눌러주세요! >> ";
                std::cin.ignore(20, '\n');
                std::cin.get();
                break;
            }

            if (!inventory.HasUsableItem())
            {
                std::cout << "사용할 수 있는 포션이 없습니다.\n";
                
                std::cout << "엔터키를 눌러주세요! >> ";
                Next();
                break;
            }

            log.DrawInventoryScreen(inventory);

            int itemChoice;
            std::cin >> itemChoice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "잘못된 입력입니다.\n";
                break;
            }

            if (itemChoice == 0)
            {
                break;
            }

            inventory.UseItem(itemChoice - 1, player);

            std::cout << "\n엔터키를 눌러주세요! >> ";
            Next();
            break;
        }

        case 6:
        {
            log.ClearScreen();
            log.DrawKillSummary();

            std::cout << "\n엔터키를 눌러주세요! >> ";
            Next();
            break;
        }

        case 0:
        {
            std::cout << "게임을 종료합니다.\n";
            return 0;
        }
        case 99: // 시연용
        {
            player.Cheat();
            Next(); // 엔터 대기
            break;
        }

        default:
        {
            std::cout << "잘못된 입력입니다.\n";
            break;
        }
        }
    }

    return 0;
}
