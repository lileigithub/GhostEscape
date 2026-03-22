#pragma once

#include <SDL3/SDL.h>

#include "Game.h"

class Object
{
protected:
    Game &game = Game::getInstance();

public:
    Object() = default;
    virtual ~Object() = default; // 所有的类不在构造函数和析构函数中做任何事

    // 不是必须重写
    virtual void init() {};
    virtual void handleEvents(SDL_Event &) {};
    virtual void update(float) {};
    virtual void render() {};
    virtual void clean() {};
};