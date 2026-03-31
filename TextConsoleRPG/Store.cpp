// Store.cpp

#include "Store.h"
#include "Player.h"
#include "Inventory.h"
#include <iostream>
// 출력 포맷(정렬 , 간격, 자리수) 조절 라이브러리라 함
#include <iomanip>

Store::Store()
    : isOpen_(false)
{
    // 상점에서 판매하는 고정 아이템 목록
    shopItems_.push_back({ "빨간 포션", 30 });
    shopItems_.push_back({ "파란 포션", 30 });
    shopItems_.push_back({ "공격의 영약", 50 });
    shopItems_.push_back({ "방어의 영약", 50 });
}

bool Store::IsOpen() const // 상점이 열렸는지 체크용
{
    return isOpen_;
}

void Store::Close()
{
    isOpen_ = false;
}

// 화면 정리용 함수
void Store::ClearScreen() const
{
    // 콘솔 화면을 완전히 지우는 대신 줄바꿈으로 새 화면처럼 보이게 처리
    std::cout << std::string(30, '\n');
}

// 절취선을 각각 구현하기보다 하나로 불러서 쓰기 편하게 함수처리
void Store::PrintBorder() const
{
    std::cout << "==================================================\n";
}

// 각 UI 타이틀 재사용을 위한 함수 설계
void Store::PrintTitle(const std::string& title) const
{
    PrintBorder();
    std::cout << "                  [ " << title << " ]\n";
    PrintBorder();
}

void Store::PrintPlayerInfo(const Player& player) const
{
    std::cout << "이름  : " << player.GetName() << '\n';
    std::cout << "레벨  : " << player.GetLevel() << '\n';
    std::cout << "HP    : " << player.GetHP() << " / " << player.GetMaxHP() << '\n';
    std::cout << "MP    : " << player.GetMP() << " / " << player.GetMaxMP() << '\n';
    std::cout << "골드  : " << player.GetGold() << " G\n";
    PrintBorder();
}

void Store::PrintMainMenu(const Player& player) const
{
    ClearScreen();
    PrintTitle("마녀의 물약 상점");
    PrintPlayerInfo(player);

    std::cout << "1. 아이템 구매\n";
    std::cout << "2. 아이템 판매\n";
    std::cout << "3. 인벤토리 확인\n";
    std::cout << "0. 상점 나가기\n";

    PrintBorder();
    std::cout << "선택 : ";
}

void Store::PrintBuyMenu(const Player& player) const
{
    ClearScreen();
    PrintTitle("아이템 구매");
    PrintPlayerInfo(player);

    for (int i = 0; i < static_cast<int>(shopItems_.size()); ++i)
    {
        std::cout << std::setw(2) << i + 1 << ". "
            << std::left << std::setw(18) << shopItems_[i].name
            << std::right << shopItems_[i].price << " G\n";
    }

    PrintBorder();
    std::cout << "0. 뒤로가기\n";
    PrintBorder();
    std::cout << "구매할 번호 : ";
}

void Store::PrintSellMenu(const Player& player, Inventory& inventory) const
{
    ClearScreen();
    PrintTitle("아이템 판매");
    PrintPlayerInfo(player);

    if (inventory.GetItemCount() == 0)
    {
        std::cout << "판매할 아이템이 없습니다.\n";
    }
    else
    {
        for (int i = 0; i < inventory.GetItemCount(); ++i)
        {
            auto item = inventory.GetItem(i);
            // 원가에서 60% 가격으로 판매금을 받도록 설계
            // 밸런스 조정 필요 시 수치 변경 가능
            int sellPrice = item.price * 60 / 100;

            // 출력 정렬을 위해 setw/ left/ right 사용
            // 사용법 setw(2) << i + 1 = 번호는 2칸
            // left << setw(18) << item.name = 아이템 이름은 18칸(왼쪽 정렬)
            // right << item.price << "G\n" = 가격은 오른쪽 정렬
            std::cout << std::setw(2) << i + 1 << ". "
                << std::left << std::setw(18) << item.name
                << std::right << sellPrice << " G\n";
        }
    }

    PrintBorder();
    std::cout << "0. 뒤로가기\n";
    PrintBorder();
    std::cout << "판매할 번호 : ";
}

void Store::Open(Player& player, Inventory& inventory)
{
    isOpen_ = true;

    while (isOpen_)
    {
        PrintMainMenu(player);

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            BuyItem(player, inventory);
            break;

        case 2:
            SellItem(player, inventory);
            break;

        case 3:
            ClearScreen();
            PrintTitle("인벤토리");
            PrintPlayerInfo(player);

            if (inventory.GetItemCount() == 0)
            {
                std::cout << "인벤토리가 비어 있습니다.\n";
            }
            else
            {
                // 인벤토리 쪽에 PrintItems()가 있으면 이걸 써도 됨
                inventory.PrintItems();
            }

            PrintBorder();
            std::cout << "엔터 대신 아무 숫자나 입력하면 돌아갑니다 : ";

            int temp;
            std::cin >> temp;
            break;

        case 0:
            ClearScreen();
            PrintTitle("상점 종료");
            std::cout << "상점을 나갑니다.\n";
            PrintBorder();
            Close();
            break;

        default:
            ClearScreen();
            PrintTitle("알림");
            std::cout << "잘못된 입력입니다.\n";
            PrintBorder();

            int temp2;
            std::cout << "아무 숫자나 입력하면 돌아갑니다 : ";
            std::cin >> temp2;
            break;
        }
    }
}

void Store::BuyItem(Player& player, Inventory& inventory)
{
    while (true)
    {
        PrintBuyMenu(player);

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
            // 입력 실패 시 처리
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0)
        {
            return;
        }

        if (choice < 1 || choice > static_cast<int>(shopItems_.size()))
        {
            ClearScreen();
            PrintTitle("알림");
            std::cout << "존재하지 않는 상품입니다.\n";
            PrintBorder();

            int temp;
            std::cout << "아무 숫자나 입력하면 돌아갑니다 : ";
            std::cin >> temp;
            continue;
        }

        const ShopItem& item = shopItems_[choice - 1];

        if (player.GetGold() < item.price)
        {
            ClearScreen();
            PrintTitle("구매 실패");
            std::cout << "골드가 부족합니다.\n";
            std::cout << item.name << " 구매에 필요한 골드 : " << item.price << " G\n";
            std::cout << "현재 보유 골드 : " << player.GetGold() << " G\n";
            PrintBorder();

            int temp;
            std::cout << "아무 숫자나 입력하면 돌아갑니다 : ";
            std::cin >> temp;
            continue;
        }

        player.loseGold(item.price);

        // 인벤토리 함수명은 팀 코드에 맞게 최종 조정
        inventory.AddItem(item.name, item.price);

        ClearScreen();
        PrintTitle("구매 완료");
        std::cout << item.name << "을(를) 구매했습니다.\n";
        std::cout << "소모 골드 : " << item.price << " G\n";
        std::cout << "남은 골드 : " << player.GetGold() << " G\n";
        PrintBorder();

        int temp;
        std::cout << "아무 숫자나 입력하면 돌아갑니다 : ";
        std::cin >> temp;
        return;
    }
}

void Store::SellItem(Player& player, Inventory& inventory)
{
    while (true)
    {
        if (inventory.GetItemCount() == 0)
        {
            ClearScreen();
            PrintTitle("판매 불가");
            std::cout << "판매할 아이템이 없습니다.\n";
            PrintBorder();

            int temp;
            std::cout << "아무 숫자나 입력하면 돌아갑니다 : ";
            std::cin >> temp;
            return;
        }

        PrintSellMenu(player, inventory);

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0)
        {
            return;
        }

        if (choice < 1 || choice > inventory.GetItemCount())
        {
            ClearScreen();
            PrintTitle("알림");
            std::cout << "존재하지 않는 아이템입니다.\n";
            PrintBorder();

            int temp;
            std::cout << "아무 숫자나 입력하면 돌아갑니다 : ";
            std::cin >> temp;
            continue;
        }

        auto item = inventory.GetItem(choice - 1);
        int sellPrice = item.price * 60 / 100;

        // 절대 변경 금지
        // 판매 순서 :
        // 1. 인벤토리에서 제거
        // 2. 골드 지급
        inventory.RemoveItem(choice - 1);
        player.gainGold(sellPrice);

        ClearScreen();
        PrintTitle("판매 완료");
        std::cout << item.name << "을(를) 판매했습니다.\n";
        std::cout << "획득 골드 : " << sellPrice << " G\n";
        std::cout << "현재 골드 : " << player.GetGold() << " G\n";
        PrintBorder();

        int temp;
        std::cout << "아무 숫자나 입력하면 돌아갑니다 : ";
        std::cin >> temp;
        return;
    }
}
