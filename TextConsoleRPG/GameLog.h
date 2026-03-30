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

    // 중요 이벤트 로그 및 처치 기록
    void AddLog(const std::string& msg);
    void RecordMonsterKill(const std::string& monsterName);
    void DrawKillSummary() const;

    // 게임 타이틀 (입력값 반환)
    int ShowMainMenu() const;

    // 캐릭터 생성 및 ESC 스탯창 대기 루프
    void SetupCharacter(Player* player) const;

    // 플레이어 스탯창
    void DrawPlayerStatScreen(const Player& player) const;

    //전투 및 스킬 메뉴
    void DrawBattleScreen(const Player& player, const Monster& monster) const;
    void DrawSkillMenu(const Player& player) const;

    //인벤토리 창
    void DrawInventoryScreen(const Inventory& inv) const;

    //기본공격(검)과 스킬공격(검기) 연출
    void DrawAttackPunch() const;
    void DrawSkillSlash() const;

    //골드 및 경험치 획득 연출
    void DrawExpGoldGain(int exp, int gold) const;

    //아이템 획득 연출
    void DrawItemDrop(const std::string& itemName) const;

    //상점 연출
    int ShowShopPrompt() const;
    void DrawShopUI() const;

    //사망시 게임 종료 및 통계
    void DrawGameOver() const;
};
