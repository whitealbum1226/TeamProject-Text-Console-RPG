#include <iostream>
#include <string>

#include "GameLog.h"
#include "Player.h"
#include "Inventory.h"
#include "Monster/Slime.h" // 경로가 다를 경우 "Monster/Slime.h" 등으로 수정해 주세요.

int main() {

    // GameLog 객체 생성
    GameLog ui;

    // 1. 타이틀 화면 테스트
    ui.DrawTitleScreen();
    std::cout << "   [테스트 모드] 엔터를 눌러 시작하세요...\n";
    std::cin.get();

    // 2. 이름 입력 및 플레이어 생성 테스트
    std::string name = ui.PromptForPlayerName();
    Player myPlayer(name);

    // 3. 모험가 탄생 아스키아트 테스트
    ui.DrawPlayerCreated(myPlayer.GetName());
    std::cout << "\n   엔터를 누르면 스탯창을 확인합니다...\n";
    std::cin.get();

    // 4. 스탯창 출력 테스트
    ui.DrawPlayerStatScreen(myPlayer);
    std::cout << "\n   엔터를 누르면 인벤토리를 확인합니다...\n";
    std::cin.get();

    // 5. 인벤토리 출력 테스트
    Inventory myInv;
    ui.DrawInventoryScreen(myInv);
    std::cout << "\n   엔터를 누르면 전투에 진입합니다...\n";
    std::cin.get();

    // 6. 몬스터 조우 및 전투 화면 테스트
    Slime slime(myPlayer.GetLevel());
    ui.AddLog("앗! 야생의 " + slime.GetName() + "이(가) 나타났다!");
    ui.DrawBattleScreen(myPlayer, slime);
    std::cout << "   엔터를 누르면 일반 공격을 시도합니다...";
    std::cin.get();

    // 7. 일반 공격 아스키아트 연출 테스트
    ui.ClearScreen();
    ui.DrawAttackPunch();
    ui.AddLog(myPlayer.GetName() + "의 공격!");
    std::cout << "\n   엔터를 누르면 스킬 공격을 시도합니다...";
    std::cin.get();

    // 8. 스킬 공격 아스키아트 연출 테스트
    ui.ClearScreen();
    ui.DrawSkillSlash();
    ui.AddLog(myPlayer.GetName() + "의 쾌속 베기! 슬라임을 처치했습니다.");
    std::cout << "\n   엔터를 누르면 보상을 획득합니다...";
    std::cin.get();

    // 9. 경험치 및 골드 획득 연출 테스트
    ui.RecordMonsterKill(slime.GetName());
    ui.ClearScreen();
    ui.DrawExpGoldGain(50, 25);
    std::cout << "\n   엔터를 누르면 몬스터 토벌 현황을 확인합니다...";
    std::cin.get();

    // 10. 토벌 통계 화면 테스트
    ui.DrawKillSummary();
    std::cout << "\n   엔터를 누르면 게임 오버 연출을 확인합니다...";
    std::cin.get();

    // 11. 게임 오버 연출 테스트
    ui.DrawGameOver();

    std::cout << "\n  [모든 UI 테스트가 성공적으로 완료되었습니다!]\n";
    return 0;
}