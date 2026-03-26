#pragma once
#include <string>
#include <iostream>

//아이템 클래스 정의.
class Item
{
public:

	std::string name;

public:

	Item(const std::string& name) {};
	virtual ~Item() {};
};



// 포션 사용시 효과들을 정리해놓은 클래스. 아직 전투시스템 구현 안돼 구체적인 구현 불가능.
class UsePotion
{
protected:

public:

	virtual void ApplyEffect() = 0;
	virtual ~UsePotion();
	virtual void IncreaseHp() = 0;
	virtual ~UsePotion();

};



//빨간 포션 클래스 정의.
class RedPotion : public Item, public UsePotion
{
public:
	void ApplyEffect() override
	{
		if (count > 0)
		{
			count--;
			std::cout << "빨간포션을 사용하셨습니다. (남은 갯수:" << count << ")" << std::endl;
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
	void ApplyEffect() override
	{
		if (count > 0)
		{
			count--;
			std::cout << "파란 포션을 사용하셨습니다. (남은 갯수:" << count << ")" << std::endl;
			IncreaseHp() override;
			{
				Player.Hp += 50; // 아직 플레이어 클래스 안만들어져서 더 구현 불가능.
			}
		}
		else
		{
			std::cout << "남은 포션이 없습니다." << std::endl;
		}
	}

private:

	size_t count = 10;
};

//인벤토리 클래스 정의.
class Inventory
{

public:

	Inventory(size_t capacity = 40) {};
	~Inventory() {};

	// 아이템 추가. 여긴 전투시스템 구현돼야 더 구체적인 구현 가능. 아니면 나중에도 아예 안쓸수도.
	void AddItem(Item* 
	{

	}
};

