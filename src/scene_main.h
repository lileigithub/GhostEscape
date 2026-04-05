#pragma once

#include "core/scene.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "core/timer.h"
class Player;
class Spawner;

class SceneMain : public Scene
{
protected:
    Player *player_ = nullptr;
    Spawner *spawner_ = nullptr;
    HUDStats *player_stats_hud_bar_ = nullptr;
    HUDText *score_hud_text_ = nullptr;
    HUDButton *button_pause_ = nullptr;
    HUDButton *button_restart_ = nullptr;
    HUDButton *button_back_ = nullptr;

    Timer *end_timer_ = nullptr;

public:
    void init() override;
    bool handleEvents(SDL_Event &event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

    void drawBackground();
    void updateScoreText();
    void updateButtonTriggers();
    void checkEndGame();
};