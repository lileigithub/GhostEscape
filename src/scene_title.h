#pragma once

#include "core/scene.h"
#include "screen/hud_text.h"
class SceneTitle : public Scene
{

protected:
    SDL_FColor bg_color_ = {1, 1, 1, 1};
    HUDText* title_ = nullptr;
    HUDText* subtitle_ = nullptr;
    float color_timer_ = 0.0f;

public:
    void init() override;
    void update(float dt) override;
    void render() override;
    void clean() override;
    void updateColor();
};