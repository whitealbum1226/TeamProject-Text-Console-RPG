// Player.h
#pragma once
#include <string>
#include <vector>

class Skill; // 스킬 클래스 전방 선언

class Player
{
public:
    Player(const std::string& name);
    ~Player(); // 소멸자 선언 추가

    // Getter
    std::string GetName() const;
    std::string GetJob() const;
    int GetLevel() const;
    int GetHP() const;
    int GetAttack() const;
    int GetDefense() const;
    int GetExp() const;
    int GetMaxExp() const;
    int GetMaxLevel() const;
    int GetMaxHP() const;
    int GetMaxMP() const;
    int GetMP() const;
    int GetGold() const;

    // Setter
    void SetName(std::string name);
    void SetJob(std::string job);
    void SetExp(int exp);
    void SetLevel(int level);
    void SetHP(int hp);
    void SetDefense(int def);
    void SetAttack(int attack);

    // 동작 함수
    void gainExp(int exp);
    void gainGold(int G);
    void loseGold(int G);
    void Heal(int hp);
    void UseMp(int mp);
    void RecoverMP(int amount);
    void TakeDamage(int takeDamage);
    void Levelup();
    void PrintStatus();
    bool IsAlive() const;

    // 스킬 관련
    void learnSkill(Skill* s) { skillList.push_back(s); }
    std::vector<Skill*>& getSkillList() { return skillList; }

private:
    std::string name_;
    std::string job_;
    int maxLevel_;
    int level_;
    int hp_;
    int maxHp_;
    int mp_;
    int maxMp_;
    int attack_;
    int exp_;
    int maxExp_;
    int def_;
    int gold_;

    // 중복으로 적혀있던 변수들 삭제 완료

    std::vector<Skill*> skillList;
};