// Monster.cpp

#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>

Monster::Monster(std::string name, int playerLevel)
	: name_(name)
{
	static bool rendInitialized = false;
	if (!rendInitialized)
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		rendInitialized = true;
	}

	int minHp = playerLevel * 20;
	int maxHp = playerLevel * 30;
	hp_ = rand() % (maxHp - minHp + 1) + minHp;

	int minAtk = playerLevel * 5;
	int maxAtk = playerLevel * 10;
	attack_ = rand() % (maxAtk - minAtk + 1) + minAtk;

	defense_ = playerLevel * 3;
}

std::string Monster::GetName()
{
	return name_;
}
int Monster::GetHP()
{
	return hp_;
}
int Monster::GetAttack()
{
	return attack_;
}
int Monster::GetDefense()
{
	return defense_;
}

void Monster::SetName(std::string name)
{
	this->name_ = name;
}
void Monster::SetHP(int hp)
{
	this->hp_ = hp;
}
void Monster::SetAttack(int attack)
{
	this->attack_ = attack;
}
void Monster::SetDefense(int defense)
{
	this->defense_ = defense;
}
void TakeDamage(Player& player)// 몬스터가 데미지를 입을 때
{
	// 해당 주석은 플레이어 완성 후 조정하고 지우면 사용 가능
	//int takeDamage = player->GetAttack() - this->GetDefense()
	//if (takeDamage <= 0)
	//{ takeDamage = 1; }
	//this->SetHP(this->GetHP() - takeDamage)
}

void PlayerAttack(Player& player) // 몬스터가 데미지를 입힐 때
{
	//int damage = this->GetAttack() - player->GetDefense()
	//if (damage == 0)
	//{ damage = 1; }
	//player->SetHP(player->GetHP() - damage)
}