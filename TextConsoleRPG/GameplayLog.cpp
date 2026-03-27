#include "GameplayLog.h"
#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
//헤더파일 전방선언

#include <iostream>
#include <cstdlib>

GameUI::GameUI(size_t maxLines) : maxLogLines(maxLines) {}

void GameUI::ClearScreen() const {
    system("cls");
}//화면 지우기

//필수 1. 중요 이벤트 로그 추가
void GameUI::AddLog(const std::string& msg) {
    eventLogs.push_back(msg);
    if (eventLogs.size() > maxLogLines) {
        eventLogs.erase(eventLogs.begin()); //오래된 로그를 삭제합니다.
    }
}

void GameUI::LogLevelUp(const std::string& name, int NewLevel) {
    AddLog(name + "의 레벨이 " + std::to_string(NewLevel) + "(으)로 올랐다!");
} //레벨업 관련 로그, 
//사용하실때 이렇게 사용하시면 됩니다. -> ui.LogLevelUp(player.GetName(), player.GetLevel());

//필수 2. 몬스터 처치 기록 및 통계 출력
void GameUI::RecordMonsterKill(const std::string& monstername) {
    bool isFound = false;

    for (size_t i = 0; i < killRecords.size(); ++i) {
        if (killRecords[i].name == monstername) {
            killRecords[i].count++;
            isFound = true;
            break;
        }
    } //잡은 적 몬스터 확인용

    if (!isFound) {
        killRecords.push_back({ monstername, 1 });
    }
}

void GameUI::DrawKillSummary() const {
    ClearScreen();
    std::cout << "\n================ [ 몬스터 토벌 현황 ] ================\n";
    if (killRecords.empty()) { // ★오류 해결: map 버전의 잔재 제거 및 수정
        std::cout << "  아직 처치한 몬스터가 없습니다.\n";
    }
    else {
        // ★오류 해결: vector 탐색 방식으로 변경
        for (size_t i = 0; i < killRecords.size(); ++i) {
            std::cout << "  - " << killRecords[i].name << " : " << killRecords[i].count << "마리\n";
        }
    }
    std::cout << "======================================================\n";
    std::cout << " 돌아가려면 엔터를 누르세요...";
    std::cin.get();
}

// 화면 출력 (Scene) 기능입니다.
void GameUI::DrawTitleScreen() const {
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
}
//ai에게 부탁했습니다.

std::string GameUI::PromptForPlayerName() const {
    std::string inputName;
    std::cout << "  모험가의 이름을 입력하세요: ";
    std::getline(std::cin, inputName);

    if (inputName.empty()) {
        std::getline(std::cin, inputName);
    }
    return inputName;
}

void GameUI::DrawInventory(const Inventory& inv) const {
    ClearScreen();
    std::cout << "\n================== [ 인벤토리 ] ==================\n";
    if (inv.itemcount == 0) {
        std::cout << "  가방이 비어있습니다.\n";
    }
    else {
        for (size_t i = 0; i < inv.itemcount; ++i) {
            if (inv.items[i] != nullptr) {
                // Inventory.h에 정의된 Item 클래스의 name 멤버 접근
                std::cout << "  " << i + 1 << ". " << inv.items[i]->name << "\n";
            }
        }
    }
    std::cout << "==================================================\n";
    std::cout << " 닫으려면 엔터를 누르세요...";
    std::cin.get();
}

void GameUI::DrawPlayerStatScreen(const Player& player) const {
    ClearScreen();
    std::cout << "\n================== [ 플레이어 정보 ] ==================\n";

    std::cout << R"(
             _._
            /   \
           | o o |
            \ - /
            /|=|\
           / | | \
            /   \
    )" << '\n';
    // 빨간줄 표시
    std::cout << "-------------------------------------------------------\n";
    std::cout << "  이름   : " << player.GetName() << "\n";
    std::cout << "  직업   : " << player.GetJob() << "\n";
    std::cout << "  레벨   : " << player.GetLevel() << "\n";
    std::cout << "  체력   : " << player.GetHP() << "\n";
    std::cout << "  공격력 : " << player.GetAttack() << "\n";
    std::cout << "  경험치 : " << player.GetExp() << "\n";
    std::cout << "=======================================================\n";
    std::cout << " 닫으려면 엔터를 누르세요...";
    std::cin.get();
}
//ai에게 부탁했습니다.

void GameUI::DrawMonsterArt(const std::string& monsterName) const {
    if (monsterName == "슬라임") {
        std::cout << R"(

⠀⠀⠀⠀⠀⠀⠀⠀⣤⣤⣤⣤⣤⣤⣤⣤⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢀⣠⣤⣤⣾⠟⠛⠛⠛⠛⠛⠛⠛⠻⣦⣤⣤⣄⠀⠀⠀⠀⠀
⠀⠀⣠⣾⡿⠟⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⠟⠿⣿⣦⣄⠀⠀⠀
⣠⣼⡿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀
⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣶⡄⠀
⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠀⠀⠀⣀⣀⠀⠀⠀⣿⣿⡇⠀
⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀⠀⣿⣿⠀⠀⠀⣯⣿⡇⠀
⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⠇⠀⠀⠀⠿⣿⠤⣤⣧⣧⣿⡇⡀
⠿⢿⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⡀⠀⠀⠀⠁⣠⣼⣿⠟⠃
⠀⠀⠿⢷⣄⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣁⣀⣀⣀⣤⣿⠿⠁⠀⠀
⠀⠀⠀⠘⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠁⠁⠀⠀⠀

        )" << '\n';
    }
    //퍼왔습니다.

    else if (monsterName == "고블린") {
        std::cout << R"(

              ,   .-'"'=;_  ,
              |\.'-~`-.`-`;/|
              \.` '.'~-.` './
              (\`,__=-'__,'/)
           _.-'-.( d\_/b ).-'-._
         /'.-'   ' .---. '   '-.`\
       /'  .' (=    (_)    =) '.  `\
      /'  .',  `-.__.-.__.-'  ,'.  `\
     (     .'.   V       V  ; '.     )
     (    |::  `-,__.-.__,-'  ::|    )
     |   /|`:.               .:'|\   |
     |  / | `:.              :' |`\  |
     | |  (  :.             .:  )  | |
     | |   ( `:.            :' )   | |
     | |    \ :.           .: /    | |
     | |     \`:.         .:'/     | |
     ) (      `\`:.     .:'/'      ) (
     (  `)_     ) `:._.:' (     _(`  )
     \  ' _)  .'           `.  (_ `  /
      \  '_) /   .'"```"'.   \ (_`  /
       `'"`  \  (         )  /  `"'`
   ___   aac  `.`.       .'.'        ___
 .`   ``"""'''--`_)     (_'--'''"""``   `.
(_(_(___...--'"'`         `'"'--...___)_)_)

        )" << '\n';
    }
    else {
        std::cout << "\n   [ " << monsterName << "의 기운이 느껴진다... ]\n\n";
    }
}
//퍼왔습니다.

void GameUI::DrawBattleScreen(const Player& player, const Monster& monster) const {
    ClearScreen();
    std::cout << "\n==================================================\n";

    // 몬스터 정보입니다.
    std::cout << " [ 야생의 " << monster.GetName() << " ] HP: " << monster.GetHP() << "\n";
    DrawMonsterArt(monster.GetName());
    std::cout << "--------------------------------------------------\n";

    // 플레이어 정보입니다.
    // 빨간줄 표시
    std::cout << " [ " << player.GetName() << " ] Lv." << player.GetLevel()
        << " | HP: " << player.GetHP() << " | Atk: " << player.GetAttack() << "\n";
    std::cout << "--------------------------------------------------\n";

    for (const auto& log : eventLogs) {
        std::cout << "  > " << log << "\n";
    }
    std::cout << "==================================================\n";
}
