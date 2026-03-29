// Troll.cpp

#include "Troll.h"

// Troll은 높은 체력과 방어력을 가진 엘리트 몬스터로 설계
// 플레이어가 쉽게 처치하지 못하도록 전투 시간을 늘리기 위함
Troll::Troll(int playerLevel)
    : Monster("Troll", playerLevel)
{
    hp_ *= 2;
    // 기본 체력의 2배 -> 전투 지속 시간 증가
    defense_ *= 1.5;
    // 방어력 증가 -> 받는 피해 감소
    attack_ *= 1.7;
    // 공격력 증가 -> 버티기만 하는게 아닌 위협적인 요소 포함
}
