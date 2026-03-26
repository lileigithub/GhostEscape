#pragma once

#include "core/actor.h"
#include "affiliates/sprite_anim.h"

class Player;

class Enemy : public Actor
{
public:
    enum State
    {
        NORMAL,
        HURT,
        DEAD
    };

protected:
    ObjectWord *target_ = nullptr;
    State current_state_ = NORMAL;
    float timer_ = 0.0f;

    SpriteAnim *normal_anim_ = nullptr;
    SpriteAnim *hurt_anim_ = nullptr;
    SpriteAnim *dead_anim_ = nullptr;

public:
    Enemy(ObjectWord *target)
    {
        target_ = target;
    }

    void init() override;
    void update(float dt) override;
    
    void setState(State state) { current_state_ = state; }
    State getState() { return current_state_; }

    void aimTarget();
    void changeState(State state);
};