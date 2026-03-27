#include "enemy.h"
#include "affiliates/sprite_anim.h"
#include "core/stats.h"

void Enemy::init()
{
    Actor::init();
    setPosition(target_->getPosition() + glm::vec2(200.0f, 200.0f));
    normal_anim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    hurt_anim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    dead_anim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    dead_anim_->setLoop(false);
    hurt_anim_->setActive(false);
    dead_anim_->setActive(false);
    collider_ = Collider::creatColliderAddChild(this, normal_anim_->getSize());
    stats_ = Stats::createStatsAddChild(this);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    aimTarget();
    Actor::move(dt);
    attack(target_);
}

void Enemy::render()
{
    Actor::render();
#ifdef DEBUG_MODE
#endif
}

bool Enemy::attack(Actor *other)
{
    if (collider_->isColliding(other->getCollider()))
    {
        stats_->takeDamage(other->getDemage());
        return true;
    }
    return false;
}

void Enemy::aimTarget()
{
    if (target_ != nullptr)
    {
        SDL_Log("Enemy screen pos : %f, %f", getScreenPos().x, getScreenPos().y);
        SDL_Log("Enemy world pos: %f, %f", getPosition().x, getPosition().y);
        SDL_Log("Player screen pos: %f, %f", target_->getScreenPos().x, target_->getScreenPos().y);
        SDL_Log("Player world pos: %f, %f", target_->getPosition().x, target_->getPosition().y);
        auto direction = target_->getPosition() - this->getPosition();
        SDL_Log("Direction: %f, %f", direction.x, direction.y);
        direction = glm::normalize(direction);
        SDL_Log("normalize Direction: %f, %f", direction.x, direction.y);
        this->velocity_ = direction * max_speed_;
    }
}

void Enemy::changeState(State state)
{
    if (state == NULL)
        return;
    if (current_state_ != state)
    {
        current_state_ = state;
        switch (state)
        {
        case State::NORMAL:
            normal_anim_->setActive(true);
            hurt_anim_->setActive(false);
            dead_anim_->setActive(false);
            break;
        case State::HURT:
            normal_anim_->setActive(false);
            hurt_anim_->setActive(true);
            dead_anim_->setActive(false);
            break;
        case State::DEAD:
            normal_anim_->setActive(false);
            hurt_anim_->setActive(false);
            dead_anim_->setActive(true);
            break;
        }
    }
}

void Enemy::dead()
{
    changeState(State::DEAD);
    // 死亡动画停止后，删除敌人
    if (!dead_anim_->isActive())
    {
        setNeedRemove(true);
    }
}
