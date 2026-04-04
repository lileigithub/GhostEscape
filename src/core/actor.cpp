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

float Actor::getDemage()
{
    if (stats_ == nullptr)
        return 0;
    return stats_->getDemage();
}

void Actor::updateHealthBar()
{
    if (stats_ && health_bar_)
    {
        health_bar_->setPercent(stats_->getCurrentHealth() / stats_->getMaxHealth());
    }
}

void Actor::takeDamage(float damage)
{
    if (stats_) {
        stats_->takeDamage(damage);
    }
}
