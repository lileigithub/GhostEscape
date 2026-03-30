#pragma once

#include "core/actor.h"
#include "affiliates/sprite_anim.h"
#include "affiliates/collider.h"

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
    Player *target_ = nullptr;
    State current_state_ = NORMAL;

    SpriteAnim *normal_anim_ = nullptr;
    SpriteAnim *hurt_anim_ = nullptr;
    SpriteAnim *dead_anim_ = nullptr;

public:
    Enemy(Player *target)
    {
        target_ = target;
    }

    void init() override;
    void update(float dt) override;
    void render() override;

    void setState(State state) { current_state_ = state; }
    State getState() { return current_state_; }

    bool attack(Actor *other);
    void aimTarget();
    void changeState(State state);
    void dead();
    void takeDamage(int) override;
};