// GameLog.h
#pragma once
#include <string>
#include <vector>
#include <iostream>

class Player;
class Monster; // 몬스터 클래스 전방 선언
class Inventory;

struct KillRecord {
    std::string name;
    int count;
};

class GameLog
{
private:
    std::vector<std::string> eventLogs;
    std::vector<KillRecord> killRecords;
    size_t maxLogLines;

    
    void DrawMonsterArt(const Monster& monster) const;

    std::string MakeHPBar(int hp, int maxHp) const; // 체력바 생성

public:
    GameLog(size_t maxLines = 6);

    void ClearScreen() const;

    //처치한 몹 기록
    void AddLog(const std::string& msg);
    void RecordMonsterKill(const std::string& monsterName);
    void DrawKillSummary() const;

    //게임 타이틀
    void DrawTitleScreen() const;

    //플레이어 스탯창
    std::string PromptForPlayerName() const;
    void DrawPlayerCreated(const std::string& name) const;
    void DrawPlayerStatScreen(const Player& player) const;

    //전투
    void DrawBattleScreen(const Player& player, const Monster& monster) const;
    void DrawSkillMenu(const Player& player) const;

    //인벤토리 창
    void DrawInventoryScreen(const Inventory& inv) const;

    //기본공격과 스킬공격
    void DrawAttackPunch() const;
    void DrawSkillSlash() const;

    //골드 및 경험치
    void DrawExpGoldGain(int exp, int gold) const;

    //사망시 게임 종료
    void DrawGameOver() const;
};