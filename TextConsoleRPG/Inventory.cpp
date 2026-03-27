#include "Inventory.h"
#include <iostream>
#include <string>

RedPotion() : Item("빨간 포션") {}
void ApplyEffect(Player& player) override
{
    if (count > 0)
    {
        count--;
        std::cout << "빨간포션을 사용하셨습니다. (남은 갯수:" << count << ")" << std::endl;
        player.Hp += 50;
        std::cout << "Hp가 50 회복되었습니다. 현재 Hp:" << player.Hp << std::endl;
    }
    else
    {
        std::cout << "남은 포션이 없습니다." << std::endl;
    }
};

BluePotion() : Item("파란 포션") {}
void ApplyEffect(Player& player) override
{
    if (count > 0)
    {
        count--;
        std::cout << "파란 포션을 사용하셨습니다. (남은 갯수:" << count << ")" << std::endl;
        player.Mp += 50;
        std::cout << "Mp가 50 회복되었습니다. 현재 Mp:" << player.Mp << std::endl;
    }
    else
    {
        std::cout << "남은 포션이 없습니다." << std::endl;
    }
};

AttackPotion() : Item("공격의 영약") {}
void ApplyEffect(Player& player) override
{
    if (count > 0)
    {
        count--;
        std::cout << "공격의 영약을 사용하셨습니다. (남은 갯수:" << count << ")" << std::endl;
        player.Attack += 5;
        std::cout << "공격력이 5 상승했습니다. 현재 공격력:" << player.Attack << std::endl;
    }
    else
    {
        std::cout << "남은 공격의 영약이 없습니다." << std::endl;
    }

};

DefensePotion() : Item("방어의 영약") {}
void ApplyEffect(Player& player) override
{
    if (count > 0)
    {
        count--;
        std::cout << "방어의 영역을 사용하셨습니다. (남은 갯수:" << count << ")" << std::endl;
        player.Defense += 5;
        std::cout << "방어력이 5 상승했습니다. 현재 방어력" << player.Defense << std::endl;
    }
    else
    {
        std::cout << "남은 방어의 영약이 없습니다." << std::endl;
    }
};

class Inventory
{
public:
    Item* items[40];
    size_t itemcount = 0;

    Inventory()
    {
        for (int i = 0; i < 40; i++)
        {
            items[i] = nullptr;
        }
    }
    void AddItem() {}// 이건 나중에 전투에서 몬스터를 죽이고 아이템을 주웠을 때 실행 예정. 아직 미구현.
};
