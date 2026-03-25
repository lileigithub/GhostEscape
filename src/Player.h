#pragma once

#include "core/actor.h"

class SpriteAnim;

class Player : public Actor
{

    SpriteAnim *idleAnim_;
    SpriteAnim *moveAnim_;
    float maxSpeed_ = 0.0f;
    bool is_moving_ = false;

public:
    Player() = default;
    ~Player() = default;

    virtual void init();
    virtual void handleEvents(SDL_Event &);
    virtual void update(float);
    virtual void render();
    virtual void clean();
    void keyBoardControl();
    void move(float deltaTime);
    void changeState();
};