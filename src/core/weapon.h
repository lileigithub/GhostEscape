#pragma once
#include "object.h"
#include "../world/spell.h"

class Actor;
class Weapon : public Object
{
protected:
    Actor * parent_ = nullptr;
    float cooldown_time_ = 1.0f;  // 冷却时间
    float cooldown_timer_ = cooldown_time_; // 冷却计时器
    int cost_mana_ = 20;          // 魔法消耗
public:
    void update(float dt) override;
    void attack(Spell *spell);
    bool canAttack();
};