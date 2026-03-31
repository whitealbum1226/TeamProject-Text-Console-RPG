//Player.h

#pragma once
#include <string>
#include <vector>

class Skill;

class Player
{
public:
    Player(const std::string& name);
    ~Player();

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
    bool GetQuickAttack() { return quickAttack; }

    void SetName(std::string name);
    void SetJob(std::string job);
    void SetLevel(int level);
    void SetHP(int hp);
    void SetDefense(int def);
    void SetAttack(int attack);
    void gainExp(int exp);
    void gainGold(int G);
    void loseGold(int G);
    void Heal(int hp);
    void UseMp(int mp);
    void RecoverMP(int mp);

    void SetQuickAttack(bool state) { quickAttack = state; }
    void learnSkill(Skill* s) { skillList.push_back(s); }
    std::vector<Skill*>& getSkillList() { return skillList; }

    void TakeDamage(int takeDamage);

    void Levelup();
    void PrintStatus();
    bool IsAlive() const;
   
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

    bool quickAttack = false; // 선공 맴버 변수
    std::vector<Skill*> skillList;
};
