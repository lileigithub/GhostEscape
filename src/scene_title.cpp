#include "scene_title.h"
#include <cmath>

void SceneTitle::init()
{
    Scene::init();
    title_ = HUDText::createHUDTextAddChild(this, "幽 灵 逃 生", game_.getSceneSize() / 2.0f - glm::vec2(0, 100),
                                            glm::vec2(game_.getSceneSize().x / 2.0f, game_.getSceneSize().y / 3.0f), 64);

    subtitle_ = HUDText::createHUDTextAddChild(this, "最高分: " + std::to_string(game_.getHighScore()), game_.getSceneSize() / 2.0f + glm::vec2(0, 100), glm::vec2(200, 50), 32);
}

void SceneTitle::update(float dt)
{
    Scene::update(dt);
    color_timer_ += dt;
    updateColor();
}

void SceneTitle::render()
{
    Scene::render();
    game_.drawBoundary({30, 30}, game_.getSceneSize() - glm::vec2(30, 30), 5, bg_color_);
}

void SceneTitle::clean()
{
    Scene::clean();
}

void SceneTitle::updateColor()
{
    bg_color_.r = 0.5f + 0.5f * sinf(color_timer_ * 0.9f);
    bg_color_.g = 0.5f + 0.5f * sinf(color_timer_ * 0.7f);
    bg_color_.b = 0.5f + 0.5f * sinf(color_timer_ * 3.0f);
}
