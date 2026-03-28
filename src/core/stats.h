#pragma once
#include "object.h"

class Actor;
class Stats : public Object
{

protected:
    Actor *parent_ = nullptr;
    int current_health_ = 100;
    int max_health_ = 100;
    int current_mana_ = 100;
    int max_mana_ = 100;
    int demage_ = 50;
    float invicible_timer_ = 0.0f; // 无敌时间计时器
    float invicible_time_ = 1.5f; // 无敌时间
    bool is_invicible_ = false; // 是否无敌
    bool is_alive_ = true; // 是否存活

public:

    void update(float dt) override;

    void takeDamage(int demage);

    static Stats *createStatsAddChild(Actor *parent, int health = 100, int mana = 100, int demage = 50);
    void setCurrentHealth(int health) { current_health_ = health; }
    int getCurrentHealth() { return current_health_; }
    void setMaxHealth(int health) { max_health_ = health; }
    int getMaxHealth() { return max_health_; }
    void setCurrentMana(int mana) { current_mana_ = mana; }
    int getCurrentMana() { return current_mana_; }
    void setMaxMana(int mana) { max_mana_ = mana; }
    int getMaxMana() { return max_mana_; }
    void setDemage(int demage) { demage_ = demage; }
    int getDemage() { return demage_; }
    void setParent(Actor *parent) { parent_ = parent; }
    Actor *getParent() { return parent_; }
    void setInvicibleTimer(float timer) { invicible_timer_ = timer; }
    float getInvicibleTimer() { return invicible_timer_; }
    void setIsAlive(bool alive) { is_alive_ = alive; }
    bool getIsAlive() { return is_alive_; }

};