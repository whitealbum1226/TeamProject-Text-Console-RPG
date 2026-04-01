// Orc.cpp

#include "Orc.h"

// Orc는 플레이어가 일정 수준 성장한 이우 등장하는 중형 몬스터로 설계
// 체력과 공격력을 높여 전투 난이도를 증가시키고, 포션 사용을 유도하는 구간
Orc::Orc(int playerLevel)
    : Monster("Orc", playerLevel)
{
    maxHp_ *= 1.5;

    hp_ *= 1.5;
    // 체력 증가 -> 전투 지속 시간 증가
    attack_ *= 1.3;
    // 공격력 증가 -> 플레이어의 체력 소모를 유도하여 포션 사용 필요성 증가
}
