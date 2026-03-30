// GameLog.cpp
#include "GameLog.h" 
#include "Player.h"
#include "Monster/Monster.h" 
#include "Monster/BossMonster.h"
#include "Inventory.h"
#include <cstdlib>

GameLog::GameLog(size_t maxLines) : maxLogLines(maxLines) {}

void GameLog::ClearScreen() const {
    system("cls"); // 콘솔 화면 초기화
}

//체력바 생성기
std::string GameLog::MakeHPBar(int hp, int maxHp) const {
    if (maxHp <= 0) return "[                    ]";
    int barLength = 20;
    int filled = (hp * barLength) / maxHp;
    if (filled < 0) filled = 0;
    if (filled > barLength) filled = barLength;

    std::string bar = "[";
    for (int i = 0; i < barLength; ++i) {
        if (i < filled) bar += "#";
        else bar += "-";
    }
    bar += "]";
    return bar;
}

// 중요 이벤트 로그 (공격, 아이템, 골드 등)

void GameLog::AddLog(const std::string& msg) {
    eventLogs.push_back(msg);
    if (eventLogs.size() > maxLogLines) {
        eventLogs.erase(eventLogs.begin());
    }
}

void GameLog::RecordMonsterKill(const std::string& monsterName) {
    bool isFound = false;
    for (size_t i = 0; i < killRecords.size(); ++i) {
        if (killRecords[i].name == monsterName) {
            killRecords[i].count++;
            isFound = true;
            break;
        }
    }
    if (!isFound) {
        killRecords.push_back({ monsterName, 1 });
    }
}

void GameLog::DrawKillSummary() const {
    ClearScreen();
    std::cout << "\n================ [ 몬스터 토벌 현황 ] ================\n";
    if (killRecords.empty()) {
        std::cout << "  아직 처치한 몬스터가 없습니다.\n";
    }
    else {
        for (size_t i = 0; i < killRecords.size(); ++i) {
            std::cout << "  - " << killRecords[i].name << " : " << killRecords[i].count << "마리\n";
        }
    }
    std::cout << "======================================================\n";
    std::cout << " 돌아가려면 엔터를 누르세요...";
    std::cin.get();
}


// 타이틀 및 플레이어 생성

void GameLog::DrawTitleScreen() const {
    ClearScreen();
    std::cout << R"(
  =========================================
       _______  _______  _______    ___    
      |       ||       ||       |  |   |   
      |    _  ||    _  ||    ___|  |   |   
      |   |_| ||   |_| ||   | __   |   |   
      |    ___||    ___||   ||  |  |   |___
      |   |    |   |    |   |_| |  |       |
      |___|    |___|    |_______|  |_______|
  =========================================
        )" << "\n\n";
    std::cout << "               1. 게임 시작\n";
    std::cout << "               2. 나가기\n";
    std::cout << "  =========================================\n";
}

std::string GameLog::PromptForPlayerName() const {
    ClearScreen();
    std::string inputName;
    std::cout << "\n  모험가의 이름을 입력하세요: ";
    std::getline(std::cin, inputName);

    if (inputName.empty()) {
        std::getline(std::cin, inputName);
    }
    return inputName;
}

void GameLog::DrawPlayerCreated(const std::string& name) const {
    ClearScreen();
    std::cout << "\n  위대한 모험가 [ " << name << " ](이)가 탄생했습니다!\n";
    std::cout << R"(
             _._
            /   \
           | o o |
            \ - /
            /|=|\
           / | | \
            /   \
    )" << '\n';
}


// ESC / 스탯창 출력 (특수문자 교체)

void GameLog::DrawPlayerStatScreen(const Player& player) const {
    ClearScreen();
    std::cout << R"(
  +========================================+
  |            [ STATS WINDOW ]            |
  +========================================+
    )" << '\n';

    std::cout << "   이름    : " << player.GetName() << " (" << player.GetJob() << ")\n";
    std::cout << "   레벨    : " << player.GetLevel() << " / " << player.GetMaxLevel() << "\n";
    std::cout << "   H P     : " << player.GetHP() << " / " << player.GetMaxHP() << "\n";
    std::cout << "   M P     : " << player.GetMP() << " / " << player.GetMaxMP() << "\n";
    std::cout << "   공격력  : " << player.GetAttack() << "\n";
    std::cout << "   방어력  : " << player.GetDefense() << "\n";
    std::cout << "   경험치  : " << player.GetExp() << " / " << player.GetMaxExp() << "\n";
    std::cout << "   소지금  : " << player.GetGold() << " G\n";
    std::cout << "  ========================================\n";
}


// 몬스터 아트 및 전투 화면


void GameLog::DrawMonsterArt(const Monster& monster) const {
    std::string monsterName = monster.GetName(); // 몬스터의 이름을 꺼냅니다.

    if (monsterName == "Slime") {
        std::cout << R"(
              요
             (  )
            (    )
           (______)
        )" << '\n';
    }
    else if (monsterName == "Goblin") {
        std::cout << R"(
               ,      ,
              /(.-""-.)\
          |\  \/      \/  /|
          | \ / =.  .= \ / |
          \( \   o\/o   / )/
           \_, '-/  \-' ,_/
             /   \__/   \
        )" << '\n';
    }
    else if (monsterName == "Orc") {
        std::cout << R"(
             __,='`````'=/__
            '//  (o) (o)  \ `'
            //|     ,     |//
            /:|   _.-._   |:\
            \||  (  _  )  ||/
             \|   `---'   |/
        )" << '\n';
    }
    else if (monsterName == "Troll") {
        std::cout << R"(
             ,      ,
            /(.-""-.)\
        |\  \/      \/  /|
        | \ / =.  .= \ / |
        \( \   o\/o   / )/
         \_,   /    \   ,_/
           /   \__/   \
           \,___/\___,/

       )" << '\n';
    }

    //보스 몬스터
    else if (monsterName == "BossDragon") {
        const BossMonster* boss = dynamic_cast<const BossMonster*>(&monster);
        bool isPhase2 = (boss != nullptr && boss->IsPhaseTwo());

        if (isPhase2) {
            std::cout << R"( 
            <>=======() 
           (/\___   /|\\          ()==========<>_
                 \_/ | \\        //|\   ______/ \)
                   \_|  \\      // | \_/
                     \|\/|\_   //  /\/
                      (oo)\ \_//  /
                     //_/\_\/ /  |
                    @@/  |=\  \  |
                         \_=\_ \ |
                           \==\ |\_
                         __(\===\(  )\
                        (((~) __(_/   |
                             (((~) \  /
                             ______/ /
                             '------'
            )" << '\n';
        }
        else {
            std::cout << R"(
                    \||/
                    |  @___oo
          /\  /\   / (__,,,,|
         ) /^\) ^\/ _)
         )   /^\/   _)
         )   _ /  / _)
      /\  )/\/ ||  | )_)
     <  >      |(,,) )__)
      ||      /    \)___)\
      | \____(      )___) )___
       \______(_______;;; __;;;
            )" << '\n';
        }
    }
    // 다른 몬스터가 아닐 때 (기본값)
    else {
        std::cout << "\n       [ 미지의 기운이 느껴진다... ]\n\n";
    }
}

// 몬스터 조우 창
void GameLog::DrawBattleScreen(const Player& player, const Monster& monster) const {
    ClearScreen();
    std::cout << "  +======================================================+\n";

    // 보스 2페이즈 이름 연출
    std::string displayName = monster.GetName();
    const BossMonster* boss = dynamic_cast<const BossMonster*>(&monster);
    if (boss != nullptr && boss->IsPhaseTwo()) {
        displayName = "★각성한 " + displayName + "★";
    }

    std::cout << "   [ 야생의 " << displayName << " ]\n";

    //체력바 적용
    std::cout << "   HP: " << MakeHPBar(monster.GetHP(), monster.GetMaxHP())
        << " (" << monster.GetHP() << "/" << monster.GetMaxHP() << ")\n";
    std::cout << "   Atk: " << monster.GetAttack() << " | Def: " << monster.GetDefense() << "\n";


    DrawMonsterArt(monster);

    std::cout << "  +------------------------------------------------------+\n";
    std::cout << "   [ " << player.GetName() << " ] Lv." << player.GetLevel() << "\n";

    //체력바 적용
    std::cout << "   HP: " << MakeHPBar(player.GetHP(), player.GetMaxHP())
        << " (" << player.GetHP() << "/" << player.GetMaxHP() << ")\n";
    std::cout << "   MP: " << MakeHPBar(player.GetMP(), player.GetMaxMP())
        << " (" << player.GetMP() << "/" << player.GetMaxMP() << ")\n";
    std::cout << "  +======================================================+\n";

    for (size_t i = 0; i < eventLogs.size(); ++i) {
        std::cout << "   > " << eventLogs[i] << "\n";
    }
    std::cout << "  +======================================================+\n";

  //전투 메뉴
    std::cout << R"(
   +=====================================================+
   |  1. 공격 (Attack)   |  2. 가방 (Inventory)          |
   |  3. 스킬 (Skill)    |  0. 도망 (Run)                |
   +=====================================================+
    )" << '\n';
}

void GameLog::DrawSkillMenu(const Player& player) const {
    std::cout << "\n   [ 스킬 목록 ]\n";
    std::cout << "   0. 취소 (뒤로가기)\n";
}

//전투 연출 아스키아트
void GameLog::DrawAttackPunch() const {
    std::cout << R"(

           /| ________________
     O|===|* >________________>
           \| 
      [ 공겨어어어억~! ]
    )" << '\n';
}

void GameLog::DrawSkillSlash() const {
    std::cout << R"(

.---------------------------------------.
      >>>>>----------[=====> 
'---------------------------------------'
         [ 쾌속 베기!! ]
    )" << '\n';
}

// 인벤토리 창
void GameLog::DrawInventoryScreen(const Inventory& inv) const {
    ClearScreen();
    std::cout << R"(
  +========================================+
  |             [ INVENTORY ]              |
  +========================================+
    )" << '\n';

    if (inv.itemcount == 0) {
        std::cout << "   가방이 비어있습니다.\n";
    }
    else {
        for (size_t i = 0; i < inv.itemcount; ++i) {
            if (inv.items[i] != nullptr) {
                std::cout << "   " << i + 1 << ". " << inv.items[i]->name << "\n";
            }
        }
    }
    std::cout << "  ========================================\n";
    std::cout << "   0. 닫기\n";
}

// 경험치 및 골드 획득 연출
void GameLog::DrawExpGoldGain(int exp, int gold) const {
    std::cout << R"(
          /\                 /\
         /  \      EXP      /  \
        /____\    +++++    /____\
    )" << '\n';
    std::cout << "   [ " << exp << " ] 의 경험치를 얻었습니다!\n";
    std::cout << "   [ " << gold << " G ] 를 획득했습니다!\n";
}

// 게임 오버
void GameLog::DrawGameOver() const {
    ClearScreen();
    std::cout << R"(
         _______  _______  __   __  _______ 
        |       ||       ||  |_|  ||       |
        |    ___||   _   ||       ||    ___|
        |   | __ |  | |  ||       ||   |___ 
        |   ||  ||  |_|  ||       ||    ___|
        |   |_| ||       || ||_|| ||   |___ 
        |_______||_______||_|   |_||_______|
                눈앞이 캄캄해졌다...
                 
         " You cannot give up just yet... "

    )" << "\n\n";
}