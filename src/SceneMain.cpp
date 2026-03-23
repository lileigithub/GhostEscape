#include "SceneMain.h"
#include "Player.h"

void SceneMain::init()
{
    setWordSize(game.getSceneSize() * 3.0f);
    player_ = new Player();
    player_->init();
}

void SceneMain::handleEvents(SDL_Event &event)
{
    player_->handleEvents(event);
}

void SceneMain::update(float dt)
{
    player_->update(dt);
    // 摄像机跟随玩家，玩家位置在摄像机中心
    setCameraPos(player_->getPosition() - game.getSceneSize() / 2.0f);
}

void SceneMain::render()
{
    drawBackground();
    player_->render();
}

void SceneMain::clean()
{
    if (player_ != nullptr)
    {
        player_->clean();
        delete player_;
        player_ = nullptr;
    }
}

void SceneMain::drawBackground()
{
    // 世界坐标系下的物体 渲染在窗口中的坐标 = 世界坐标 - 摄像机坐标
    glm::vec2 word_left_top_pos_in_screen = -getCameraPos();
    glm::vec2 word_right_bottom_pos_screen = getWordSize() - getCameraPos();
    game.drawGrid(word_left_top_pos_in_screen, word_right_bottom_pos_screen, {80, 80}, {0.5f, 0.5f, 0.5f, 1.0f});
}
