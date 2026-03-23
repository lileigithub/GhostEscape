#include "ObjectWord.h"
#include "Scene.h"

void ObjectWord::update(float dt)
{
    ObjectWord::update(dt);
    //世界坐标更新后，屏幕坐标需要更新
    screenPos_ = game.getCurrentScene() ->wordPosToScreenPos(position_);
}

void ObjectWord::setPosition(const glm::vec2 &position)
{
    position_ = position;
    screenPos_ = game.getCurrentScene() ->wordPosToScreenPos(position);
}

void ObjectWord::setScreenPos(const glm::vec2 &screenPos)
{
    screenPos_ = screenPos;
    position_ = game.getCurrentScene() ->screenPosToWorldPos(screenPos);
}
