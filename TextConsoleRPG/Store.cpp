// Store.cpp

#include "Store.h"
#include "Player.h"
#include "Inventory.h"
#include "GameLog.h"
#include <iostream>
#include <iomanip>

GameLog UI;
// 게임 로그 상점메인화면 불러오기 용

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
    // 다른 파트는 다른 사용방법 썻는데 본인은 할줄 아는 범위 내에서 작성한게 이거..
    std::cout << std::string(30, '\n');
}

// 절취선을 각각 구현하기보다 하나로 불러서 쓰기 편하게 함수처리
void Store::PrintLine() const
{
    std::cout << "==================================================\n";
}

// 각각 입력 안해도 이거 하나 가져다 쓰면 머릿말 사용가능
void Store::PrintMainString(const std::string& MainString) const
{
    PrintLine();
    std::cout << "                  [ " << MainString << " ]\n";
    PrintLine();
}

void Store::PrintPlayerInfo(const Player& player) const
{
    std::cout << "이름  : " << player.GetName() << '\n';
    std::cout << "레벨  : " << player.GetLevel() << '\n';
    std::cout << "HP    : " << player.GetHP() << " / " << player.GetMaxHP() << '\n';
    std::cout << "MP    : " << player.GetMP() << " / " << player.GetMaxMP() << '\n';
    std::cout << "골드  : " << player.GetGold() << " G\n";
    PrintLine();
}

// 혹시나 재사용 가능성 있어서 함수 삭제는 안함
// 일단 사용은 X
void Store::PrintMainMenu(const Player& player) const
{
    ClearScreen();
    PrintMainString("마녀의 물약 상점");
    PrintPlayerInfo(player);

    std::cout << "1. 아이템 구매\n";
    std::cout << "2. 아이템 판매\n";
    std::cout << "3. 인벤토리 확인\n";
    std::cout << "0. 상점 나가기\n";

    PrintLine();
    std::cout << "선택 : ";
}

// 상점에서 판매하는 아이템 보는 함수
void Store::PrintBuyMenu(const Player& player) const
{
    ClearScreen();
    PrintMainString("아이템 구매");
    PrintPlayerInfo(player);

    for (int i = 0; i < static_cast<int>(shopItems_.size()); ++i)
    {
        std::cout << std::setw(2) << i + 1 << ". "
            << std::left << std::setw(18) << shopItems_[i].name
            << std::right << shopItems_[i].price << " G\n";
    }

    PrintLine();
    std::cout << "0. 뒤로가기\n";
    PrintLine();
    std::cout << "구매할 번호 : ";
}

void Store::PrintSellMenu(const Player& player, Inventory& inventory) const
{
    ClearScreen();
    PrintMainString("아이템 판매");
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

           // 정렬 사용을 위해 작성
           // 내 머릿속에서 나온거 x 참고자료 보고 만듬
            std::cout << std::setw(2) << i + 1 << ". "
                << std::left << std::setw(18) << item.name
                << std::right << sellPrice << " G\n";
        }
    }

    PrintLine();
    std::cout << "0. 뒤로가기\n";
    PrintLine();
    std::cout << "판매할 번호 : ";
}

// 상점 이용하기 위한 함수
// 다른 파트에서 이거 호출해서 쓰면됨
void Store::Open(Player& player, Inventory& inventory)
{
    isOpen_ = true;

    while (isOpen_)
    {
        UI.DrawShopUI();

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
            // 혹시나 입력 실수 체크용
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            // 강의에서 배운 잘못들어간 값 지우기
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

        case 0:
            ClearScreen();
            PrintMainString("상점 종료");
            std::cout << "상점을 나갑니다.\n";
            PrintLine();
            Close();
            break;

        default:
            ClearScreen();
            PrintMainString("알림");
            std::cout << "잘못된 입력입니다.\n";
            PrintLine();

       
            break;
        }
    }
}

// 아이템 구매 함수
void Store::BuyItem(Player& player, Inventory& inventory)
{
    while (true)
    {
        PrintBuyMenu(player);

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

        if (choice < 1 || choice > static_cast<int>(shopItems_.size()))
        {
            ClearScreen();
            PrintMainString("알림");
            std::cout << "존재하지 않는 상품입니다.\n";
            PrintLine();

            continue;
        }

        const ShopItem& item = shopItems_[choice - 1];

        if (player.GetGold() < item.price)
        {
            ClearScreen();
            PrintMainString("구매 실패");
            std::cout << "골드가 부족합니다.\n";
            std::cout << item.name << " 구매에 필요한 골드 : " << item.price << " G\n";
            std::cout << "현재 보유 골드 : " << player.GetGold() << " G\n";
            PrintLine();

       
            continue;
        }

        player.loseGold(item.price);

        inventory.AddItem(item.name, item.price);

        ClearScreen();
        PrintMainString("구매 완료");
        std::cout << item.name << "을(를) 구매했습니다.\n";
        std::cout << "소모 골드 : " << item.price << " G\n";
        std::cout << "남은 골드 : " << player.GetGold() << " G\n";
        PrintLine();

     
        return;
    }
}

// 플레이어가 아이템 판매하는 함수
void Store::SellItem(Player& player, Inventory& inventory)
{
    while (true)
    {
        if (inventory.GetItemCount() == 0)
        {
            ClearScreen();
            PrintMainString("판매 불가");
            std::cout << "판매할 아이템이 없습니다.\n";
            PrintLine();

      
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
            PrintMainString("알림");
            std::cout << "존재하지 않는 아이템입니다.\n";
            PrintLine();

      
            continue;
        }

        auto item = inventory.GetItem(choice - 1);
        int sellPrice = item.price * 60 / 100;

        // 절대 변경 금지
        // 판매 순서 중요함
        // 1. 인벤토리에서 제거
        // 2. 골드 지급
        inventory.RemoveItem(choice - 1);
        player.gainGold(sellPrice);

        ClearScreen();
        PrintMainString("판매 완료");
        std::cout << item.name << "을(를) 판매했습니다.\n";
        std::cout << "획득 골드 : " << sellPrice << " G\n";
        std::cout << "현재 골드 : " << player.GetGold() << " G\n";
        PrintLine();

      
        return;
    }
}
