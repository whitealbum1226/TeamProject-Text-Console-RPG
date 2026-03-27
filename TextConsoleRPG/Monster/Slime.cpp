// Slime.cpp

#include "Slime.h"

// Slime은 초반에 등장하는 기본 몬스터로 설계
// 플레이어가 무리 없이 처치하며 쉽게 성장할 수 있게 난이도를 낮춤
Slime::Slime(int playerLevel)
    : Monster("Slime", playerLevel)
{
    hp_ *= 0.5;
    // 체력 감소 -> 빠른 처치 가능
    attack_ *= 0.7;
    // 공격력 감소 -> 플레이어의 체력 관리 부담 감소
    defense_ = 0;
    // 방어력 없음 -> 데미지가 그대로 들어가도록 설계
}
