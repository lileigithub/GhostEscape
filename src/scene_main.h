#pragma once

#include "core/scene.h"

class Player;
class Spawner;
class UI_Mouse;

class SceneMain : public Scene
{
protected:
    Player *player_ = nullptr;
    Spawner *spawner_ = nullptr;
    UI_Mouse *ui_mouse_ = nullptr;

public:
    void init() override;
    void handleEvents(SDL_Event &event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

    void drawBackground();
};