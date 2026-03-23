#pragma once

#include "core/Scene.h"

class SceneMain : public Scene
{
private:
    glm::vec2 word_size_ = glm::vec2(0);

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