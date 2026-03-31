// Store.h

#pragma once
#include <string>
#include <vector>

class Player;
class Inventory;

struct ShopItem
{
    std::string name;
    int price;
};

class Store
{
public:
    Store();

    void Open(Player& player, Inventory& inventory);
    bool IsOpen() const;

private:
    bool isOpen_;
    std::vector<ShopItem> shopItems_;

    void Close();

    void ClearScreen() const;
    void PrintLine() const;
    void PrintMainString(const std::string& title) const;
    void PrintPlayerInfo(const Player& player) const;

    void PrintMainMenu(const Player& player) const;
    void PrintBuyMenu(const Player& player) const;
    void PrintSellMenu(const Player& player, Inventory& inventory) const;

    void BuyItem(Player& player, Inventory& inventory);
    void SellItem(Player& player, Inventory& inventory);
};
