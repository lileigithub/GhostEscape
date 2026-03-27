#include "actor.h"
#include "scene.h"
#include "stats.h"

void Actor::move(float deltaTime)
{
    setPosition(glm::clamp(getPosition() + velocity_ * deltaTime, glm::vec2(), game_.getCurrentScene()->getWordSize()));
}

int Actor::getDemage()
{
    if (stats_ == nullptr)
        return 0;
    return stats_->getDemage();
}
