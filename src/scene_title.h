#pragma once

#include "core/scene.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
class SceneTitle : public Scene
{

protected:
    SDL_FColor bg_color_ = {1, 1, 1, 1};
    HUDText* title_ = nullptr;
    HUDText* subtitle_ = nullptr;
    float color_timer_ = 0.0f;
    HUDButton* button_start_ = nullptr;
    HUDButton* button_credits_ = nullptr;
    HUDButton* button_exit_ = nullptr;
    HUDText* text_credits_ = nullptr;

public:
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;
    void updateColor();
    void updateButtonTriggers();
};