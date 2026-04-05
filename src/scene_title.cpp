#include "scene_title.h"
#include "scene_main.h"
#include "screen/ui_mouse.h"
#include <cmath>

void SceneTitle::init()
{
    Scene::init();
    title_ = HUDText::createHUDTextAddChild(this, "幽 灵 逃 生", game_.getSceneSize() / 2.0f - glm::vec2(0, 100),
                                            glm::vec2(game_.getSceneSize().x / 2.0f, game_.getSceneSize().y / 3.0f), 64);

    subtitle_ = HUDText::createHUDTextAddChild(this, "最高分: " + std::to_string(game_.getHighScore()), game_.getSceneSize() / 2.0f + glm::vec2(0, 100), glm::vec2(200, 50), 32);

    button_start_ = HUDButton::createHUDButtonAddChild(this, game_.getSceneSize() / 2.0f + glm::vec2(-200, 200),
                                                       "assets/UI/A_Start1.png", "assets/UI/A_Start2.png", "assets/UI/A_Start3.png", 2.0f);
    button_credits_ = HUDButton::createHUDButtonAddChild(this, game_.getSceneSize() / 2.0f + glm::vec2(0, 200),
                                                         "assets/UI/A_Credits1.png", "assets/UI/A_Credits2.png", "assets/UI/A_Credits3.png", 2.0f);
    button_exit_ = HUDButton::createHUDButtonAddChild(this, game_.getSceneSize() / 2.0f + glm::vec2(200, 200),
                                                      "assets/UI/A_Quit1.png", "assets/UI/A_Quit2.png", "assets/UI/A_Quit3.png", 2.0f);
    text_credits_ = HUDText::createHUDTextAddChild(this, game_.loadTextFile("assets/credits.txt"), glm::vec2(game_.getSceneSize().x / 2.0f, game_.getSceneSize().y / 2.0f), glm::vec2(500, 500));
    text_credits_->setBgSzieByText(50.0f);
    text_credits_->setActive(false);

    ui_mouse_ = UI_Mouse::createUiMouseAddChild(this, "assets/UI/pointer_c_shaded.png", "assets/UI/pointer_c_shaded.png");
}

bool SceneTitle::handleEvents(SDL_Event &event)
{
    if (text_credits_->getIsActive())
    {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            text_credits_->setActive(false);
            return true;
        }
        else
        {
            return false;
        }
    }
    return Scene::handleEvents(event);
}

void SceneTitle::update(float dt)
{
    color_timer_ += dt;
    updateColor();
    if (text_credits_->getIsActive())
    {
        button_start_->setFreezed(true);
        button_credits_->setFreezed(true);
        button_exit_->setFreezed(true);
    }
    else
    {
        updateButtonTriggers();
        button_start_->setFreezed(false);
        button_credits_->setFreezed(false);
        button_exit_->setFreezed(false);
    }
    Scene::update(dt);
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

void SceneTitle::updateButtonTriggers()
{
    if (button_exit_->getResetTrigger())
    {
        game_.setIsRunning(false);
    }
    else if (button_start_->getResetTrigger())
    {
        game_.changeScene(new SceneMain());
    }
    else if (button_credits_->getResetTrigger())
    {
        text_credits_->setActive(true);
    }
}
