#pragma once

#include "core/scene.h"

class Player;

class SceneMain : public Scene
{
private:
    Player *player_ = nullptr;

public:
    void init() override;
    void handleEvents(SDL_Event &event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

    void drawBackground();
};