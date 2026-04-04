#pragma once
#include "object_world.h"

class Actor;
class Stats : public ObjectWorld
{

protected:
    Actor *parent_ = nullptr;
    float current_health_ = 100;
    float max_health_ = 100;
    float current_mana_ = 100;
    float max_mana_ = 100;
    float restore_mana_ = 5; // 每秒回复的魔法值
    float demage_ = 50;
    float invicible_timer_ = 0.0f; // 无敌时间计时器
    float invicible_time_ = 1.5f; // 无敌时间
    bool is_invicible_ = false; // 是否无敌
    bool is_alive_ = true; // 是否存活

public:

    void update(float dt) override;

    void takeDamage(float demage) override;

    bool canUseMana(int manaCost) {
        return current_mana_ >= manaCost;
    }

    void useMana(int manaCost) {
        current_mana_ -= manaCost;
        if (current_mana_ < 0) {
            current_mana_ = 0;
        }
    }

    static Stats *createStatsAddChild(Actor *parent, float health = 100, float mana = 100, float demage = 50);
    void setCurrentHealth(float health) { current_health_ = health; }
    float getCurrentHealth() { return current_health_; }
    void setMaxHealth(float health) { max_health_ = health; }
    float getMaxHealth() { return max_health_; }
    void setCurrentMana(float mana) { current_mana_ = mana; }
    float getCurrentMana() { return current_mana_; }
    void setMaxMana(float mana) { max_mana_ = mana; }
    float getMaxMana() { return max_mana_; }
    void setDemage(float demage) { demage_ = demage; }
    float getDemage() { return demage_; }
    void setParent(Actor *parent) { parent_ = parent; }
    Actor *getParent() { return parent_; }
    void setInvicibleTimer(float timer) { invicible_timer_ = timer; }
    float getInvicibleTimer() { return invicible_timer_; }
    void setIsAlive(bool alive) { is_alive_ = alive; }
    bool getIsAlive() { return is_alive_; }
    bool getIsInvicible() { return is_invicible_; }

};