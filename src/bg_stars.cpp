#include "bg_stars.h"
#include "core/scene.h"

BgStars *BgStars::createBgStarsAddChild(Object *parent, int stars_num, float scale_near, float scale_mid, float scale_far)
{
    BgStars *bg_stars = new BgStars();
    bg_stars->stars_num_ = stars_num;
    bg_stars->scale_near_ = scale_near;
    bg_stars->scale_mid_ = scale_mid;
    bg_stars->scale_far_ = scale_far;
    bg_stars->generateStarsPos();
    if (parent)
    {
        parent->addChild(bg_stars);
    }
    return bg_stars;
}

void BgStars::update(float dt)
{
    Object::update(dt);
    color_timer_ += dt;
    color_near_ = {0.5f + 0.5f * sinf(dt * 3.0f), 0.5f + 0.5f * sinf(color_timer_ * 0.5f), 0.5f + 0.5f * sinf(color_timer_ * 0.2f), 1};
    color_mid_ = {0.5f + 0.5f * sinf(dt * 2.0f), 0.5f + 0.5f * sinf(color_timer_ * 0.5f), 0.5f + 0.5f * sinf(color_timer_ * 0.4f), 1};
    color_far_ = {0.5f + 0.5f * sinf(dt * 1.0f), 0.5f + 0.5f * sinf(color_timer_ * 0.2f), 0.5f + 0.5f * sinf(color_timer_ * 0.1f), 1};
    /* color_near_ = {1, 0, 0};
    color_mid_ = {0, 1, 0};
    color_far_ = {0, 0, 1}; */
}

void BgStars::render()
{
    Object::render();
    // 渲染坐标 = 世界坐标 - 相机坐标 * 1, 和摄像机在一个平面（比如这个游戏里的网格）
    // 渲染坐标 = 世界坐标 - 相机坐标 * 0, 最最远的背景，几乎不动
    // 渲染坐标 = 世界坐标 - 相机坐标 * 比例（越远越小）
    for (auto it = stars_pos_far_.begin(); it != stars_pos_far_.end(); ++it)
    {
        glm::vec2 pos = *it;
        game_.drawPoint(pos - game_.getCurrentScene()->getCameraPos() * scale_far_ , color_far_);
    }
    for (auto it = stars_pos_mid_.begin(); it != stars_pos_mid_.end(); ++it)
    {
        glm::vec2 pos = *it;
        game_.drawPoint(pos - game_.getCurrentScene()->getCameraPos() * scale_mid_ , color_mid_);
    }
    for (auto it = stars_pos_near_.begin(); it != stars_pos_near_.end(); ++it)
    {
        glm::vec2 pos = *it;
        game_.drawPoint(pos - game_.getCurrentScene()->getCameraPos() * scale_near_ , color_near_);
    }
}

void BgStars::generateStarsPos()
{
    stars_pos_near_.reserve(stars_num_);
    stars_pos_mid_.reserve(stars_num_);
    stars_pos_far_.reserve(stars_num_);
    glm::vec2 diffBgSize = game_.getCurrentScene()->getWordSize() - game_.getSceneSize();
    for (int i = 0; i < stars_num_; ++i)
    {
        stars_pos_near_.push_back(game_.randomVec2({0,0}, game_.getSceneSize() + diffBgSize * scale_near_));
        stars_pos_mid_.push_back(game_.randomVec2({0,0}, game_.getSceneSize() + diffBgSize * scale_mid_));
        stars_pos_far_.push_back(game_.randomVec2({0,0}, game_.getSceneSize() + diffBgSize * scale_mid_));
    }
}
