// Inventory.cpp

#include "Inventory.h"
#include <iostream>

Inventory::Inventory()
    : itemcount(0)
{
    for (int i = 0; i < 40; ++i)
    {
        items[i] = nullptr;
    }
}

Inventory::~Inventory()
{
    for (size_t i = 0; i < itemcount; ++i)
    {
        delete items[i];
        items[i] = nullptr;
    }
}

void RedPotion::ApplyEffect(Player& player)
{
    std::cout << "빨간 포션을 사용했습니다.\n";
    player.Heal(50);
    std::cout << "HP가 50 회복되었습니다.\n";
}

void BluePotion::ApplyEffect(Player& player)
{
    std::cout << "파란 포션을 사용했습니다.\n";
    player.RecoverMP(50);
    std::cout << "MP가 50 회복되었습니다.\n";
}

void AttackPotion::ApplyEffect(Player& player)
{
    std::cout << "공격의 영약을 사용했습니다.\n";
    player.SetAttack(player.GetAttack() + 5);
    std::cout << "공격력이 5 증가했습니다.\n";
}

void DefensePotion::ApplyEffect(Player& player)
{
    std::cout << "방어의 영약을 사용했습니다.\n";
    player.SetDefense(player.GetDefense() + 5);
    std::cout << "방어력이 5 증가했습니다.\n";
}

bool Inventory::AddItem(const std::string& name, int price)
{
    for (size_t i = 0; i < itemcount; ++i)
    {
        if (items[i] != nullptr && items[i]->name_ == name)
        {
            items[i]->count_++;
            return true;
        }
    }

    if (itemcount >= 40)
    {
        std::cout << "인벤토리가 가득 찼습니다.\n";
        return false;
    }

    if (name == "빨간 포션")
    {
        items[itemcount] = new RedPotion();
    }
    else if (name == "파란 포션")
    {
        items[itemcount] = new BluePotion();
    }
    else if (name == "공격의 영약")
    {
        items[itemcount] = new AttackPotion();
    }
    else if (name == "방어의 영약")
    {
        items[itemcount] = new DefensePotion();
    }
    else
    {
        std::cout << "알 수 없는 아이템입니다.\n";
        return false;
    }

    ++itemcount;
    return true;
}

bool Inventory::RemoveItem(int index)
{
    if (index < 0 || index >= static_cast<int>(itemcount))
    {
        return false;
    }

    if (items[index] == nullptr)
    {
        return false;
    }

    if (items[index]->count_ > 1)
    {
        items[index]->count_--;
        return true;
    }

    delete items[index];
    items[index] = nullptr;

    for (size_t i = index; i < itemcount - 1; ++i)
    {
        items[i] = items[i + 1];
    }

    items[itemcount - 1] = nullptr;
    --itemcount;

    return true;
}

int Inventory::GetItemCount() const
{
    return static_cast<int>(itemcount);
}

InventoryItemData Inventory::GetItem(int index) const
{
    if (index < 0 || index >= static_cast<int>(itemcount))
    {
        return { "", 0, 0 };
    }

    if (items[index] == nullptr)
    {
        return { "", 0, 0 };
    }

    return { items[index]->name_, items[index]->price_, items[index]->count_ };
}

void Inventory::PrintItems() const
{
    if (itemcount == 0)
    {
        std::cout << "인벤토리가 비어 있습니다.\n";
        return;
    }

    for (size_t i = 0; i < itemcount; ++i)
    {
        if (items[i] != nullptr)
        {
            std::cout << i + 1 << ". "
                << items[i]->name_
                << " x" << items[i]->count_
                << " (" << items[i]->price_ << " G)\n";
        }
    }
}

bool Inventory::HasUsableItem() const
{
    if (itemcount == 0)
    {
        return false;
    }

    for (size_t i = 0; i < itemcount; ++i)
    {
        if (items[i] != nullptr && items[i]->count_ > 0)
        {
            return true;
        }
    }

    return false;
}

void Inventory::UseItem(int index, Player& player)
{
    if (itemcount == 0)
    {
        std::cout << "인벤토리가 비어 있어 사용할 포션이 없습니다.\n";
        return;
    }

    if (index < 0 || index >= static_cast<int>(itemcount))
    {
        std::cout << "잘못된 아이템 번호입니다.\n";
        return;
    }

    if (items[index] == nullptr)
    {
        std::cout << "해당 칸에 아이템이 없습니다.\n";
        return;
    }

    if (items[index]->count_ <= 0)
    {
        std::cout << "이 포션은 남아있지 않습니다.\n";
        return;
    }

    UsePotion* potion = dynamic_cast<UsePotion*>(items[index]);
    if (potion == nullptr)
    {
        std::cout << "사용할 수 있는 포션이 아닙니다.\n";
        return;
    }

    potion->ApplyEffect(player);
    RemoveItem(index);
}
