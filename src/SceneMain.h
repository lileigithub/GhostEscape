#pragma once

#include "core/Scene.h"

class SceneMain : public Scene
{
public:
    SceneMain() = default;
    ~SceneMain() = default;

    void init() override;
    void handleEvents(SDL_Event &event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;
};