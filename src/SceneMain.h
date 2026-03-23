#pragma once

#include "core/Scene.h"

class Player;

class SceneMain : public Scene
{
private:
    Player *player_ = nullptr;

public:
    SceneMain() = default;
    ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void drawBackground();
};