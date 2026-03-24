#pragma once

#include "core/actor.h"

class Player : public Actor{

    float maxSpeed_ = 0.0f;
    
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
};