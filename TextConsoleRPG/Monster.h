// Monster.h

#pragma once
#include <string>

class Monster
{
public:
	Monster(std::string name, int playerLevel);

	virtual ~Monster() {};
	virtual void TakeDamage(Player& player);
	virtual void PlayerAttack(Player& player);

	std::string GetName();
	int GetHP();
	int GetAttack();
	int GetDefense();

	void SetName(std::string name);
	void SetHP(int hp);
	void SetAttack(int attack);
	void SetDefense(int defense);

private:
	std::string name_;
	int hp_;
	int attack_;
	int defense_;
};