
﻿#pragma once
#include <string>
#include <iostream>

class Player
{
public:
    size_t hp_ = 50;
    size_t Attack = 10;
};

// 아이템 클래스 정의
class Item
{
public:
    std::string name;
    Item(const std::string& name) : name(name) {};
    virtual ~Item() {};
};

//'포션을 사용한 상황'을 클래스화해봤습니다.
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

class AttackPotion : public Item, public UsePotion
{
public:
    AttackPotion() : Item("공격의 영약") {}
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
