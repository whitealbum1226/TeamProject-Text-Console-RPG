
﻿#pragma once
#include <string>
#include <iostream>

class Player // Player가 이런식으로 대충 만들어졌다고 가정. 얼마든지 갈아엎어질 수 있음.
{
public:
    size_t Hp = 50;
    size_t Mp = 50;
    size_t Attack = 10;
    size_t Defense = 10;
};

//아이템 클래스 정의.
class Item
{
public:
    std::string name;
    Item(const std::string& name) : name(name) {};
    virtual ~Item() {};
};

class UsePotion
{
protected:
public:
    virtual void ApplyEffect(Player& player) = 0;
    virtual ~UsePotion() {};
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
    void AddItem();// 이건 나중에 전투에서 몬스터를 죽이고 아이템을 주웠을 때 실행 예정. 아직 미구현.
};
