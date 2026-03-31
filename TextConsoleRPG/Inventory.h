// Inventory.h

#pragma once
#include <string>
#include <iostream>
#include "Player.h"

struct InventoryItemData
{
    std::string name;
    int price;
    int count;
};

class Item
{
public:
    std::string name_;
    int price_;
    int count_;

    Item(const std::string& name, int price, int count = 1)
        : name_(name), price_(price), count_(count)
    {
    }

    virtual ~Item() {}
};

class UsePotion
{
public:
    virtual void ApplyEffect(Player& player) = 0;
    virtual ~UsePotion() {}
};

class RedPotion : public Item, public UsePotion
{
public:
    RedPotion() : Item("빨간 포션", 30, 1) {}
    void ApplyEffect(Player& player) override;
};

class BluePotion : public Item, public UsePotion
{
public:
    BluePotion() : Item("파란 포션", 30, 1) {}
    void ApplyEffect(Player& player) override;
};

class AttackPotion : public Item, public UsePotion
{
public:
    AttackPotion() : Item("공격의 영약", 50, 1) {}
    void ApplyEffect(Player& player) override;
};

class DefensePotion : public Item, public UsePotion
{
public:
    DefensePotion() : Item("방어의 영약", 50, 1) {}
    void ApplyEffect(Player& player) override;
};

class Inventory
{
public:
    Item* items[40];
    size_t itemcount;

    Inventory();
    ~Inventory();

    bool AddItem(const std::string& name, int price);
    bool RemoveItem(int index);
    int GetItemCount() const;
    InventoryItemData GetItem(int index) const;
    void PrintItems() const;
    void UseItem(int index, Player& player);
    bool HasUsableItem() const;
};
