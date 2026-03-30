// Inventory.h
#pragma once
#include <string>
#include <iostream>

class Player;

class Item
{
public:
    std::string name;
    Item(const std::string& name) : name(name) {}
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
    RedPotion() : Item("빨간 포션") {}
    void ApplyEffect(Player& player) override;
private:
    size_t count = 10;
};

class BluePotion : public Item, public UsePotion
{
public:
    BluePotion() : Item("파란 포션") {}
    void ApplyEffect(Player& player) override;
private:
    size_t count = 10;
};

class AttackPotion : public Item, public UsePotion
{
public:
    AttackPotion() : Item("공격의 영약") {}
    void ApplyEffect(Player& player) override;
private:
    size_t count = 3;
};

class DefensePotion : public Item, public UsePotion
{
public:
    DefensePotion() : Item("방어의 영약") {}
    void ApplyEffect(Player& player) override;
private:
    size_t count = 3;
};

class Inventory
{
public:
    Item* items[40];
    size_t itemcount = 0;

    Inventory();
    void AddItem();
};