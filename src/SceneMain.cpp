#include "SceneMain.h"

void SceneMain::init()
{
    word_size_ = game.getSceneSize() * 3.0f;
}

void SceneMain::handleEvents(SDL_Event &)
{
}

void SceneMain::update(float dt)
{
}

void SceneMain::render()
{
    drawBackground();
}

void SceneMain::clean()
{
}

void SceneMain::drawBackground()
{
    // 世界坐标系下的物体 渲染在窗口中的坐标 = 世界坐标 - 摄像机坐标
    glm::vec2 word_left_top_pos_in_screen = -camera_pos_;
    glm::vec2 word_right_bottom_pos_screen = word_size_ - camera_pos_;
    game.drawGrid(word_left_top_pos_in_screen, word_right_bottom_pos_screen, {80, 80}, {0.5f, 0.5f, 0.5f, 1.0f});
}
