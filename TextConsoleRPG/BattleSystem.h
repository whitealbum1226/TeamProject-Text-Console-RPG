#pragma once

#include <iostream>

class Player;
class Monster;
class GameLog;
class Inventory;
class Blood;
class Skill;

class BattleSystem
{
private:
    Player* player;
    Monster* monster;
    GameLog* logSystem;
    Inventory* inventory;
    Blood* blood;
    int turn = 1;
    
    bool ExecuteSkill(Skill* selectedSkill);


public:
    BattleSystem(Player* p, Monster* m, GameLog* lg, Inventory* inv);

    void BattleReady();

    bool NextTurn();

    void PlayerWin();

    void PlayerAttack();

    void MonsterAttack();

    void BattleStart();
};
