#pragma once

#include "core/actor.h"
class Effect;
class SpriteAnim;
class WeaponThunder;

class Player : public Actor
{
    SpriteAnim *idleAnim_;
    SpriteAnim *moveAnim_;
    WeaponThunder *weapon_;

public:
    Player() = default;
    ~Player() = default;

    void init() override;
    bool handleEvents(SDL_Event &) override;
    void update(float) override;
    void render() override;
    void clean() override;
    void keyBoardControl();
    void changeState();
    void whenDead();
    void takeDamage(float damage) override;
};