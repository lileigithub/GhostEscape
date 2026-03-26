#include "enemy.h"
#include "affiliates/sprite_anim.h"

void Enemy::init()
{
    Actor::init();
    setPosition(target_->getPosition() + glm::vec2(200.0f, 200.0f));
    Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghost-Sheet.png", 2.0f);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    aimTarget();
    Actor::move(dt);
}

void Enemy::aimTarget()
{
    if (target_ != nullptr)
    {
        auto direction = target_->getPosition() - this->getPosition();
        direction = glm::normalize(direction);
        this->velocity_ = direction * max_speed_;
    }
}