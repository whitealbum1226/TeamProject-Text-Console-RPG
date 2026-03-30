#pragma once

#include <iostream>

class Player;
class Monster;

class BattleSystem
{
private:
    Player* player;
    Monster* monster;
    int turn = 1;
    Blood* blood;

public:
    BattleSystem(Player* p, Monster* m);

    void BattleReady();

    void NextTurn();

    void PlayerWin();

    void PlayerAttack();

    void MonsterAttack();

    void BattleStart();
};
