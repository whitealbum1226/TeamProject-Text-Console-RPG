// GameLog.h
#pragma once
#include <string>
#include <vector>

//헤더 파일이 많아져서 전방선언했습니다.

class Player;
class Monster;
class Inventory;

//몬스터 처치기록 담당 구조체 입니다.
struct KillRecord {
    std::string name;
    int count;
};

class GameUI
{
private:
    std::vector<std::string> eventLogs; //전투, 아이템, 골드의 중요한 로그를 보관합니다.          
    std::vector<KillRecord> killRecords;//몬스터 처치 통계를 보관합니다. (이름 충돌 방지: s 추가)
    size_t maxLogLines; //화면에 표시할 로그 줄 수의 리미트입니다.

    void ClearScreen() const;
    void DrawMonsterArt(const std::string& monsterName) const;

public:
    GameUI(size_t maxLines = 6); //최대 출력수는 6줄로 제한합니다.

    //로그 기능관련 함수들입니다.
    void AddLog(const std::string& msg);
    void RecordMonsterKill(const std::string& monsterName); //몬스터 처치관련 함수입니다.
    void DrawKillSummary() const; //몬스터 처치 수 통계확인 화면입니다.

    //UI기능입니다.
    void DrawTitleScreen() const;
    std::string PromptForPlayerName() const;
    void DrawInventory(const Inventory& inv) const; //인벤토리 관련창 ui입니다.
    void DrawBattleScreen(const Player& player, const Monster& monster) const; //전투창 관련 ui입니다.

    void DrawPlayerStatScreen(const Player& player) const; //플레이어의 스테이터스를 나타내는 관련 ui입니다.
    void LogLevelUp(const std::string& name, int NewLevel); //레벨업 관련 로그입니다.
};
