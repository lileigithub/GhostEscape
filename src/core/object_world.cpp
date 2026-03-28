#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt);
    //世界坐标更新后，屏幕坐标需要更新
    screen_pos_ = game_.getCurrentScene() ->wordPosToScreenPos(position_);
}

void ObjectWorld::setPosition(const glm::vec2 &position)
{
    position_ = position;
    screen_pos_ = game_.getCurrentScene() -> wordPosToScreenPos(position_);
}

void ObjectWorld::setScreenPos(const glm::vec2 &screenPos)
{
    screen_pos_ = screenPos;
    position_ = game_.getCurrentScene() ->screenPosToWorldPos(screenPos);
}
