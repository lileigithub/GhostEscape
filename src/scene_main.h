#pragma once

#include "core/scene.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
class Player;
class Spawner;

class SceneMain : public Scene
{
protected:
    Player *player_ = nullptr;
    Spawner *spawner_ = nullptr;
    HUDStats *player_stats_hud_bar_ = nullptr;
    HUDText *score_hud_text_ = nullptr;

public:
    void init() override;
    void handleEvents(SDL_Event &event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

    void drawBackground();
    void updateScoreText();
};