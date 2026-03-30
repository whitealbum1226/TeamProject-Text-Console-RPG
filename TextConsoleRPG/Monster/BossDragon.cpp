// BossDragon.cpp

#include "BossDragon.h"

BossDragon::BossDragon(int playerLevel)
    : BossMonster("BossDragon", playerLevel)
{
}

void BossDragon::SpecialAttack()
{
    // int SpecialDamage = attack_ * 2;
    if (isPhaseTwo_)
    {
        // SpecialDamage = attack_ * 3;
        HellFireBreath();
        // 2페이지 전투 데미지 배율 적용 예정
    }
    else
    {
        FireBreath();
        // 기본 특수 공격 데미지 처리 예정
    }
}

void BossDragon::UsePattern()
{
    if (!isPhaseTwo_)
    {
        int pattern = rand() % 3;

        switch (pattern)
        {
        case 0:
            TailSwing();
            break;
        case 1:
            DownwardStrike();
            break;
        case 2:
            Roar();
            break;
        }
    }
    else
    {
        int pattern = rand() % 2;

        switch (pattern)
        {
        case 0:
            HellFireTailSwing();
            break;
        case 1:
            Roar();
            break;
        }
    }
}

void BossDragon::TailSwing()
{
    std::cout << name_ << " 테일 스윙!\n";
    // BattleSystem에서 기본 물리 공격 데미지 적용
}
void BossDragon::DownwardStrike()
{
    std::cout << name_ << " 내려찍기!\n";
    // BattleSystem에서 기본 물리 공격 데미지 적용
}

void BossDragon::FireBreath()
{
    std::cout << name_ << " 파이어 브레스!\n";
    // BattleSystem에서 기본 스킬 데미지 적용
}
void BossDragon::Roar()
{
    std::cout << name_ << " 포효!\n";
    // BattleSystem에서 디버프 또는상태 이상 연계 가능
    // 보스 1턴용 버프기로도 가능
}

void BossDragon::HellFireBreath()
{
    std::cout << name_ << " 헬 파이어 브레스!!\n";
    // BattleSystem에서 2페이즈 강화 스킬 데미지 적용
}
void BossDragon::HellFireTailSwing()
{
    std::cout << name_ << " 헬 파이어 테일 스윙!!\n";
    // BattleSystem에서 2페이즈 강화 물리 데미지 적용
}


// 배틀 구현때 참고용
//std::cout << "\n===== 보스 전투 시작 =====\n";
//std::cout << boss.GetName() << " 이(가) 나타났다!!\n";

//while (boss.GetHP() > 0 && player.GetHP() > 0)
//{
    // 플레이어 턴
//    player.Attack(boss);

//    if (boss.GetHP() <= 0)
//    {
//        std::cout << "보스 처치!!\n";
//        break;
//    }

    // 보스 턴
//    boss.IncreaseTurnCount();

//    if (boss.GetTurnCount() % 3 == 0)
//    {
//        boss.SpecialAttack();
//    }
//    else
//    {
//        boss.Attack(player);
//    }
//}
