// GameLog.h
#pragma once
#include <string>
#include <vector>
#include <iostream>


class Player;
class Monster;
class Inventory;
class Skill;

//클래스 전방선언

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
    std::string MakeBar(int current, int max, char fillChar) const; // 체력및마나

public:
    GameLog(size_t maxLines = 6);

    void ClearScreen() const;

    //이벤트 로그 및 처치 기록
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

    //기본공격과 스킬들
    void DrawAttackPunch() const;
    void DrawSkillSlash() const;

    //[새로 추가한 스킬 Ui 함수들]
    void DrawSkillQuick() const;
    void DrawSkillHeal() const;
    void DrawSkillBlood() const;
    void DrawSkillBoom() const;
    void DrawSkillManaBurn() const;
    void DrawSkillRoulette() const;
    void DrawSkillMultiStrike() const;

    //골드 및 경험치 획득 연출
    void DrawExpGoldGain(int exp, int gold) const;

    //아이템 획득 연출
    void DrawItemDrop(const std::string& itemName) const;

    //상점 연출
    int ShowShopPrompt() const;
    void DrawShopUI() const;

    //사망시 게임 종료 및 통계
    void DrawGameOver() const;

   //보스공격
    void DrawBossAttackEffect(const std::string& attackName) const;

    //스킬 상세설명ui
    void DrawSkillDetail(Skill* skill) const;
};
