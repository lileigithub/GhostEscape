#include "scene_main.h"
#include "Enemy.h"
#include "player.h"
#include "screen/ui_mouse.h"
#include "spawner.h"
#include "world/effect.h"
#include "world/spell.h"
void SceneMain::init()
{
    Scene::init();
    setWordSize(game_.getSceneSize() * 3.0f);
    player_ = new Player();
    player_->init();
    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setPlayer(player_);
    addChild(spawner_);
    addChild(player_); // 让玩家比敌人后渲染
    ui_mouse_ = UI_Mouse::createUiMouseAddChild(this, "assets/UI/29.png", "assets/UI/30.png");
}

void SceneMain::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event);
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            auto pos = ui_mouse_->getScreenPos() + getCameraPos();
            Spell::createSpellAddChild(ui_mouse_, "assets/effect/Thunderstrike w blur.png", pos, 50, 5, 9, 3.0f);
        }
    }
}

void SceneMain::update(float dt)
{
    // 摄像机跟随玩家，玩家位置在摄像机中心
    setCameraPos(player_->getPosition() - game_.getSceneSize() / 2.0f);
    Scene::update(dt);
}

void SceneMain::render()
{
    drawBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
    // 加入child里的，都由Scene清理了，这里不用管了
}

void SceneMain::drawBackground()
{
    // 世界坐标系下的物体 渲染在窗口中的坐标 = 世界坐标 - 摄像机坐标
    glm::vec2 word_left_top_pos_in_screen = -getCameraPos();
    glm::vec2 word_right_bottom_pos_screen = getWordSize() - getCameraPos();
    game_.drawGrid(word_left_top_pos_in_screen, word_right_bottom_pos_screen, {80, 80}, {0.5f, 0.5f, 0.5f, 1.0f});
}
