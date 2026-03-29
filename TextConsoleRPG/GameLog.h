// GameLog.h
#pragma once
#include <string>
#include <vector>
#include <iostream>

class Player;
class Monster;
class Inventory;

struct KillRecord {
    std::string name;
    int count;
};

class GameLog
{
private:
    std::vector<std::string> eventLogs;    // 전투, 아이템 사용 등 중요 이벤트 로그
    std::vector<KillRecord> killRecords;   // 몬스터 처치 기록
    size_t maxLogLines;

    void DrawMonsterArt(const std::string& monsterName) const;

public:
    GameLog(size_t maxLines = 6); // 생성자 이름도 GameLog

    void ClearScreen() const;

    // --- 로그 및 처치 통계 ---
    void AddLog(const std::string& msg);
    void RecordMonsterKill(const std::string& monsterName);
    void DrawKillSummary() const;

    // --- 기본 UI (타이틀, 이름 입력, 스탯창) ---
    void DrawTitleScreen() const;
    std::string PromptForPlayerName() const;
    void DrawPlayerCreated(const std::string& name) const;
    void DrawPlayerStatScreen(const Player& player) const;

    // --- 전투 화면 및 메뉴 ---
    void DrawBattleScreen(const Player& player, const Monster& monster) const;
    void DrawSkillMenu(const Player& player) const;

    // --- 인벤토리 UI ---
    void DrawInventoryScreen(const Inventory& inv) const;

    // --- 전투 연출 아스키아트 ---
    void DrawAttackPunch() const;
    void DrawSkillSlash() const;

    // --- 보상 연출 (경험치, 골드) ---
    void DrawExpGoldGain(int exp, int gold) const;

    // --- 사망 연출 ---
    void DrawGameOver() const;
};