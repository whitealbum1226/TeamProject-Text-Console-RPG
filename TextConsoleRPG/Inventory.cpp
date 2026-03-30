#include "Inventory.h"
#include <iostream>
#include <string>

RedPotion() : Item("빨간 포션") {}
void RedPotion::ApplyEffect(Player& player) override
{
    if (count_ > 0)
    {
        count_--;
        std::cout << "빨간포션을 사용하셨습니다. (남은 갯수:" << count_ << ")" << std::endl;
        player.hp_ += 50;
        std::cout << "Hp가 50 회복되었습니다. 현재 Hp:" << player.hp_ << std::endl;
    }
    else
    {
        std::cout << "남은 포션이 없습니다." << std::endl;
    }
};

BluePotion() : Item("파란 포션") {}
void BluePotion::ApplyEffect(Player& player) override
{
    if (count_ > 0)
    {
        count_--;
        std::cout << "파란 포션을 사용하셨습니다. (남은 갯수:" << count_ << ")" << std::endl;
        player.mp_ += 50;
        std::cout << "Mp가 50 회복되었습니다. 현재 Mp:" << player.mp_ << std::endl;
    }
    else
    {
        std::cout << "남은 포션이 없습니다." << std::endl;
    }
};

AttackPotion() : Item("공격의 영약") {}
void AttakcPotion::ApplyEffect(Player& player) override
{
    if (count_ > 0)
    {
        count_--;
        std::cout << "공격의 영약을 사용하셨습니다. (남은 갯수:" << count_ << ")" << std::endl;
        player.attack_ += 5;
        std::cout << "공격력이 5 상승했습니다. 현재 공격력:" << player.attack_ << std::endl;
    }
    else
    {
        std::cout << "남은 공격의 영약이 없습니다." << std::endl;
    }

};

DefensePotion() : Item("방어의 영약") {}
void DefensePotion::ApplyEffect(Player& player) override
{
    if (count_ > 0)
    {
        count_--;
        std::cout << "방어의 영역을 사용하셨습니다. (남은 갯수:" << count_ << ")" << std::endl;
        player.def_ += 5;
        std::cout << "방어력이 5 상승했습니다. 현재 방어력" << player.def_ << std::endl;
    }
    else
    {
        std::cout << "남은 방어의 영약이 없습니다." << std::endl;
    }
};

class Inventory
{
public:
    Item* items[4];
    Inventory()
    {
        items[0] = nullptr;
        items[1] = nullptr;
        items[2] = nullptr;
        items[3] = nullptr;
    }
    void AddItem(Item* newItem)
    {

    }
};
