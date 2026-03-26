#pragma once
#include <string>
#include <iostream>

class Player // Player가 이런식으로 대충 만들어졌다고 가정.
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

// 포션 사용시 효과들을 정리해놓은 클래스. 아직 전투시스템 구현 안돼 구체적인 구현 불가능.
class UsePotion
{
protected:
public:
    virtual void ApplyEffect(Player& player) = 0;
    virtual ~UsePotion() {};
};

//빨간 포션 클래스 정의.
class RedPotion : public Item, public UsePotion
{
public:
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
	}
private:
    size_t count = 10;
};

// 파란 포션 클래스 정의.
class BluePotion : public Item, public UsePotion
{
public:
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
	}

private:
    size_t count = 10;
};

class AttackPotion : public Item, public UsePotion
{
public:
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

    }
private:
    size_t count = 3;
};

class DefensePotion : public Item, public UsePotion
{
public:
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
    }
public:
    size_t count = 3;
};

//인벤토리 클래스 정의.
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
    void AddItem() {}// 이건 나중에 전투에서 몬스터를 죽이면 아이템을 주웠을 때 실행 예정. 아직 미구현.
};

