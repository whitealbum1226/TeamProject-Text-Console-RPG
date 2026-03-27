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

public:
    BattleSystem(Player* p, Monster* m);

    void BattleReady();

    void PlayerWin();

    void PlayerAttack();

    void MonsterAttack();

    void BattleStart();
};
