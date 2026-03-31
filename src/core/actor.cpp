#include "actor.h"
#include "scene.h"
#include "stats.h"

void Actor::update(float dt)
{
    ObjectWorld::update(dt);
    updateHealthBar();
}

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

void Actor::updateHealthBar()
{
    if (stats_ && health_bar_)
    {
        health_bar_->setPercent(static_cast<float>(stats_->getCurrentHealth()) / static_cast<float>(stats_->getMaxHealth()));
        SDL_Log("currentHealth: %d, maxHealth: %d, getPercent: %f", stats_->getCurrentHealth(), stats_->getMaxHealth(), health_bar_->getPercent());
    }
}
