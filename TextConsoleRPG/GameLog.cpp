// GameLog.cpp
#include "GameLog.h" 
#include "Player.h"
#include "Monster/Monster.h" 
#include "Monster/BossMonster.h"
#include "Inventory.h"
#include <cstdlib>

GameLog::GameLog(size_t maxLines) : maxLogLines(maxLines) {}

void GameLog::ClearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 체력바 생성기
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

// 중요 이벤트 로그
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
    std::cout << "\n================ [ 몬스터 토벌 현황 ] ================\n";
    if (killRecords.empty()) {
        std::cout << "  아직 처치한 몬스터가 없습니다.\n";
    }
    else {
        for (size_t i = 0; i < killRecords.size(); ++i) {
            std::cout << "  - [ " << killRecords[i].name << " ] : " << killRecords[i].count << " 마리 처치\n";
        }
    }
    std::cout << "======================================================\n";
}

// 타이틀
int GameLog::ShowMainMenu() const {
    ClearScreen();
    int choice = 0;
    std::cout << R"(
  _______         _    _____                       _      _____  _____  _____  
 |__   __|       | |  / ____|                     | |    |  __ \|  __ \|  __ \ 
    | | ___  __ _| |_| |     ___  _ __  ___  ___ | | ___| |__) | |__) | |  \/ 
    | |/ _ \ \/ /| __| |    / _ \| '_ \/ __|/ _ \| |/ _ \  _  /|  ___/| | __  
    | |  __/>  < | |_| |___| (_) | | | \__ \ (_) | |  __/ | \ \| |    | |_\ \ 
    |_|\___/_/\_\ \__|\_____\___/|_| |_|___/\___/|_|\___|_|  \_\_|    \____/ 
    )" << "\n\n";
    std::cout << "============================================================\n";
    std::cout << "                       1. 게임 시작                         \n";
    std::cout << "                       2. 게임 종료                         \n";
    std::cout << "============================================================\n";

    while (true) {
        std::cout << "  선택 >> ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            continue;
        }
        if (choice == 1 || choice == 2) break;
    }
    return choice;
}

// 플레이어 이름 설정 및 대기열
void GameLog::SetupCharacter(Player* player) const {
    ClearScreen();
    std::string inputName;
    std::cout << "\n  모험가의 이름을 입력하세요: ";
    std::cin >> inputName;
    player->SetName(inputName);

    int choice;
    while (true) {
        ClearScreen();
        std::cout << "\n  모험가 [ " << player->GetName() << " ]님, 어서오세요.\n";
        std::cout << R"(
                 ,
                /| ________________
          O|===|* >________________>
                \|
        )" << '\n';
        std::cout << "  ======================================================\n";
        std::cout << "    [1] 스탯창 확인   |   [0] 모험 시작\n";
        std::cout << "  ======================================================\n";
        std::cout << "  선택 >> ";

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            continue;
        }

        if (choice == 1) {
            DrawPlayerStatScreen(*player);
            std::string dummy;
            std::cout << "\n  돌아가려면 아무 글자나 입력하고 엔터를 누르세요 >> ";
            std::cin >> dummy;
        }
        else if (choice == 0) {
            break;
        }
    }
}

// 스탯창 출력
void GameLog::DrawPlayerStatScreen(const Player& player) const {
    ClearScreen();
    std::cout << R"(
============================================================
                [ 캐 릭 터  스 탯 창 ]
============================================================
    )" << '\n';

    std::cout << "   이름    : " << player.GetName() << " (" << player.GetJob() << ")\n";
    std::cout << "   레벨    : " << player.GetLevel() << " / " << player.GetMaxLevel() << "\n";
    std::cout << "   H P     : " << player.GetHP() << " / " << player.GetMaxHP() << "\n";
    std::cout << "   M P     : " << player.GetMP() << " / " << player.GetMaxMP() << "\n";
    std::cout << "   공격력  : " << player.GetAttack() << "\n";
    std::cout << "   방어력  : " << player.GetDefense() << "\n";
    std::cout << "   경험치  : " << player.GetExp() << " / " << player.GetMaxExp() << "\n";
    std::cout << "   소지금  : " << player.GetGold() << " G\n";
    std::cout << "============================================================\n";
}

// 몬스터 아트 출력
void GameLog::DrawMonsterArt(const Monster& monster) const {
    std::string monsterName = monster.GetName();

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
    else if (monsterName == "BossDragon") {
        const BossMonster* boss = dynamic_cast<const BossMonster*>(&monster);
        if (boss != nullptr && boss->IsPhaseTwo()) {
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
    else {
        std::cout << "\n       [ 미지의 기운이 느껴진다... ]\n\n";
    }
}

// 전투 화면
void GameLog::DrawBattleScreen(const Player& player, const Monster& monster) const {
    ClearScreen();
    std::cout << "============================================================\n";

    std::string displayName = monster.GetName();
    const BossMonster* boss = dynamic_cast<const BossMonster*>(&monster);
    if (boss != nullptr && boss->IsPhaseTwo()) {
        displayName = "★각성한 " + displayName + "★";
    }

    std::cout << "  [ 야생의 " << displayName << " ]\n";
    std::cout << "  HP: " << MakeHPBar(monster.GetHP(), monster.GetMaxHP())
        << " (" << monster.GetHP() << "/" << monster.GetMaxHP() << ")\n";

    DrawMonsterArt(monster);

    std::cout << "------------------------------------------------------------\n";
    std::cout << "  [ " << player.GetName() << " ] Lv." << player.GetLevel() << "\n";
    std::cout << "  HP: " << MakeHPBar(player.GetHP(), player.GetMaxHP())
        << " (" << player.GetHP() << "/" << player.GetMaxHP() << ")\n";
    std::cout << "  MP: " << MakeHPBar(player.GetMP(), player.GetMaxMP())
        << " (" << player.GetMP() << "/" << player.GetMaxMP() << ")\n";
    std::cout << "============================================================\n";

    std::cout << " [ 전투 로그 ]\n";
    for (size_t i = 0; i < eventLogs.size(); ++i) {
        std::cout << "  > " << eventLogs[i] << "\n";
    }

    for (size_t i = eventLogs.size(); i < maxLogLines; ++i) {
        std::cout << "\n";
    }
    std::cout << "============================================================\n";

    std::cout << " [1] 일반 공격     [2] 인벤토리     [3] 스킬     [0] 도망\n";
    std::cout << " 선택 >> ";
}

// 스킬 목록 화면
void GameLog::DrawSkillMenu(const Player& player) const {
    std::cout << "\n   [ 스킬 목록 ]\n";
    // BattleSystem에서 실제 스킬 목록 출력
    std::cout << "   0. 취소 (뒤로가기)\n";
    std::cout << "   선택 >> ";
}

// 기본공격 및 스킬공격 연출 (_getch 대체 적용)
void GameLog::DrawAttackPunch() const {
    ClearScreen();
    std::cout << "\n\n";
    std::cout << R"(
             />_________________________________
        O===[><_   (챙강!)                      >
             \>"""""""""""""""""""""""""""""""""
    )" << '\n';
    std::cout << "\n  날카로운 검으로 적을 공격합니다!\n";

    std::string dummy;
    std::cout << "\n  (계속하려면 아무 글자나 입력하고 엔터) >> ";
    std::cin >> dummy;
}

void GameLog::DrawSkillSlash() const {
    ClearScreen();
    std::cout << "\n\n";
    std::cout << R"(
            //
           //    (샤아악!)
          //
         //
    )" << '\n';
    std::cout << "\n  강력한 검기를 날립니다!\n";

    std::string dummy;
    std::cout << "\n  (계속하려면 아무 글자나 입력하고 엔터) >> ";
    std::cin >> dummy;
}

// 인벤토리 창
void GameLog::DrawInventoryScreen(const Inventory& inv) const {
    ClearScreen();
    std::cout << R"(
============================================================
                     [ 인 벤 토 리 ]
============================================================
    )" << '\n';

    if (inv.itemcount == 0) {
        std::cout << "   가방이 비어있습니다. (사용 가능한 포션 없음)\n";
    }
    else {
        for (size_t i = 0; i < 40; ++i) {
            if (inv.items[i] != nullptr) {
                std::cout << "   " << i + 1 << ". " << inv.items[i]->name_ << "\n";
            }
        }
    }
    std::cout << "============================================================\n";
    std::cout << "   0. 취소 (뒤로가기)\n";
    std::cout << "   선택 >> ";
}

// 경험치 및 골드 획득 연출 (_getch 대체 적용)
void GameLog::DrawExpGoldGain(int exp, int gold) const {
    std::cout << "\n";
    std::cout << R"(
     _____  __   __  _____  
    |  ___| \ \ / / |  __ \ 
    | |__    \ V /  | |__) |
    |  __|    > <   |  ___/ 
    | |___   / . \  | |     
    |_____| /_/ \_\ |_|     
    )" << '\n';
    std::cout << "  +" << exp << " EXP 획득!\n";

    std::cout << R"(
       _______
      /       \
     |  GOLD!  |
      \_______/
    )" << '\n';
    std::cout << "  +" << gold << " G 획득!\n";

    std::string dummy;
    std::cout << "\n  (계속하려면 아무 글자나 입력하고 엔터) >> ";
    std::cin >> dummy;
}

// 아이템 드롭 연출 (_getch 대체 적용)
void GameLog::DrawItemDrop(const std::string& itemName) const {
    std::cout << R"(
         /\
        /  \
       /____\
      (______)
    )" << '\n';
    std::cout << "  [" << itemName << "] 을(를) 획득했습니다!\n";

    std::string dummy;
    std::cout << "\n  (계속하려면 아무 글자나 입력하고 엔터) >> ";
    std::cin >> dummy;
}

// 상점 메뉴 및 UI
int GameLog::ShowShopPrompt() const {
    int choice;
    std::cout << "\n============================================================\n";
    std::cout << "  상점을 발견했습니다! 들어가시겠습니까?\n";
    std::cout << "  [1] 예     [2] 아니오\n";
    std::cout << " 선택 >> ";
    std::cin >> choice;
    return choice;
}

void GameLog::DrawShopUI() const {
    ClearScreen();
    std::cout << R"(
============================================================
                     [ 잡 화 상 점 ]
      ___
     /   \   "어서오세요! 좋은 물건이 많습니다."
    | o o | 
     \_-_/
============================================================
  [1] 아이템 구매
  [2] 아이템 판매
  [0] 나가기
============================================================
선택 >> )";
}

// 게임 오버
void GameLog::DrawGameOver() const {
    ClearScreen();
    std::cout << R"(
============================================================
   _____          __  __  ______    ____ __      __ ______ 
  / ____|   /\   |  \/  ||  ____|  / __ \\ \    / /|  ____|
 | |  __   /  \  | \  / || |__    | |  | |\ \  / / | |__   
 | | |_ | / /\ \ | |\/| ||  __|   | |  | | \ \/ /  |  __|  
 | |__| |/ ____ \| |  | || |____  | |__| |  \  /   | |____ 
  \_____/_/    \_\_|  |_||______|  \____/    \/    |______|
============================================================
)" << "\n";
    std::cout << R"(
                  (x_x)  <- 쓰러진 모험가...
                 /| | \
                 /   \
    )" << "\n";

    DrawKillSummary();
}
