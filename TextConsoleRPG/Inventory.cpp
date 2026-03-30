// Inventory.cpp
#include "Inventory.h"
#include "Player.h" // ★ 가짜 플레이어가 아닌 진짜 플레이어를 조작하기 위해 반드시 추가!
#include <iostream>
#include <string>

// ★ RedPotion 소속임을 명시 (RedPotion::)
void RedPotion::ApplyEffect(Player& player)
{
    if (count > 0)
    {
        count--;
        std::cout << "빨간포션을 사용하셨습니다. (남은 갯수:" << count << ")\n";
        player.Heal(50); // ★ 직접 변수에 접근하지 않고 Heal 함수 사용!
        std::cout << "Hp가 50 회복되었습니다. 현재 Hp:" << player.GetHP() << "\n";
    }
    else
    {
        std::cout << "남은 포션이 없습니다.\n";
    }
}

// ★ BluePotion 소속임을 명시 (BluePotion::)
void BluePotion::ApplyEffect(Player& player)
{
    if (count > 0)
    {
        count--;
        std::cout << "파란 포션을 사용하셨습니다. (남은 갯수:" << count << ")\n";
        player.RecoverMP(50); // ★ MP 회복 함수 사용!
        std::cout << "Mp가 50 회복되었습니다. 현재 Mp:" << player.GetMP() << "\n";
    }
    else
    {
        std::cout << "남은 포션이 없습니다.\n";
    }
}

// ★ AttackPotion 소속임을 명시 (AttackPotion::)
void AttackPotion::ApplyEffect(Player& player)
{
    if (count > 0)
    {
        count--;
        std::cout << "공격의 영약을 사용하셨습니다. (남은 갯수:" << count << ")\n";
        player.SetAttack(player.GetAttack() + 5); // ★ 기존 공격력 + 5
        std::cout << "공격력이 5 상승했습니다. 현재 공격력:" << player.GetAttack() << "\n";
    }
    else
    {
        std::cout << "남은 공격의 영약이 없습니다.\n";
    }
}

// ★ DefensePotion 소속임을 명시 (DefensePotion::)
void DefensePotion::ApplyEffect(Player& player)
{
    if (count > 0)
    {
        count--;
        std::cout << "방어의 영약을 사용하셨습니다. (남은 갯수:" << count << ")\n";
        player.SetDefense(player.GetDefense() + 5); // ★ 기존 방어력 + 5
        std::cout << "방어력이 5 상승했습니다. 현재 방어력:" << player.GetDefense() << "\n";
    }
    else
    {
        std::cout << "남은 방어의 영약이 없습니다.\n";
    }
}

// ★ cpp 파일 안에 있던 class Inventory { } 껍데기를 지우고, 함수 구현만 깔끔하게 남겼습니다.
Inventory::Inventory()
{
    itemcount = 0;
    for (int i = 0; i < 40; i++)
    {
        items[i] = nullptr;
    }
}

void Inventory::AddItem()
{
    // 나중에 아이템 획득 시 구현할 곳
}