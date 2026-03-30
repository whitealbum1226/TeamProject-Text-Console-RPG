// Store.h

#pragma once
#include <string>
#include <vector>

class Player;
class Inventory;

struct ShopItem // class로 추가 설계하기보단 struct으로 단순 데이터 관리는 이게 맞다 판단.
{
    std::string name;
    int price;
};

enum class StoreResult
{
    Success,
    NotEnoughGold,
    InvalidIndex,
    InventoryEmpty,
    StoreClosed
};

class Store
{
public:
    Store();

    void Open();
    void Close();
    bool IsOpen() const;

    const std::vector<ShopItem>& GetShopItems() const;
    // UI/Log에 데이터를 넘겨주기 위함

    StoreResult BuyItem(int index, Player& player, Inventory& inventory); // Player 은 gold, Inventory 는 item을 각각 담당하고 있기에 둘다 호출
    StoreResult SellItem(int index, Player& player, Inventory& inventory);

private:
    bool isOpen_;
    std::vector<ShopItem> shopItems_;
};
