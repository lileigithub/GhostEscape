#include "enemy.h"
#include "affiliates/affiliate_bar.h"
#include "affiliates/sprite_anim.h"
#include "core/stats.h"
#include "player.h"
void Enemy::init()
{
    Actor::init();
    normal_anim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    hurt_anim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    dead_anim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    dead_anim_->setLoop(false);
    hurt_anim_->setActive(false);
    dead_anim_->setActive(false);
    collider_ = Collider::creatColliderAddChild(this, normal_anim_->getSize());
    stats_ = Stats::createStatsAddChild(this);
    object_type_ = ObjectType::ENEMY;
    health_bar_ = AffiliateBar::createAffiliateBarAddChild(this, {normal_anim_->getSize().x, 10}, Anchor::BOTTOM_CENTER);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2{0, normal_anim_->getSize().y / 2});
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    if (stats_->getCurrentHealth() <= 0)
    {
        dead();
    }
    else if (stats_->getIsInvicible())
    {
        changeState(State::HURT);
    }
    else
    {
        changeState(State::NORMAL);
    }
    if (target_->getIsActive())
    {
        aimTarget();
        Actor::move(dt);
        attack(target_);
    }
}

void Enemy::render()
{
    Actor::render();
}

bool Enemy::attack(Actor *other)
{
    if (collider_->isColliding(other->getCollider()))
    {
        other->takeDamage(stats_->getDemage());
        return true;
    }
    return false;
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

void Enemy::changeState(State state)
{
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
    if (dead_anim_->getIsFinish())
    {
        game_.setScore(game_.getScore() + 10);
        setNeedRemove(true);
    }
}
