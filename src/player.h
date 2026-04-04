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

    virtual void init();
    virtual void handleEvents(SDL_Event &);
    virtual void update(float);
    virtual void render();
    virtual void clean();
    void keyBoardControl();
    void changeState();
    void whenDead();
    void takeDamage(float damage) override;
};