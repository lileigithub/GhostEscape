#include "actor.h"
#include "scene.h"

void Actor::move(float deltaTime)
{
    setPosition(glm::clamp(getPosition() + velocity_ * deltaTime, glm::vec2(), game_.getCurrentScene()->getWordSize()));
}