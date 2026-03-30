#include "player.h"
#include "affiliates/sprite_anim.h"
#include "core/scene.h"
#include "core/stats.h"
#include "world/effect.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.f;
    setPosition(game_.getCurrentScene()->getWordSize() / 2.0f);
    idleAnim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghost-idle.png", 2.0f);
    moveAnim_ = Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghost-move.png", 2.0f);
    collider_ = Collider::creatColliderAddChild(this, idleAnim_->getSize() / 2.0f);
    stats_ = Stats::createStatsAddChild(this);
    
};
void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}
void Player::update(float dt)
{
    Actor::update(dt);
    keyBoardControl();
    Actor::move(dt);
    changeState();
    whenDead();
}
void Player::render()
{
    Actor::render();
#ifdef DEBUG_MODE
    game_.drawRect({getScreenPos().x, getScreenPos().y, 10.0f, 10.0f}, {255, 255, 255, 255});
#endif
}
void Player::clean()
{
    Actor::clean();
}
void Player::keyBoardControl()
{
    velocity_ *= 0.9f;

    float xSpeedVelocity = 0.0f;
    float ySpeedVelocity = 0.0f;

    auto keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP])
    {
        ySpeedVelocity -= max_speed_;
    }
    if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN])
    {
        ySpeedVelocity += max_speed_;
    }
    if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT])
    {
        xSpeedVelocity -= max_speed_;
    }
    if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT])
    {
        xSpeedVelocity += max_speed_;
    }
    velocity_.x = xSpeedVelocity;
    velocity_.y = ySpeedVelocity;
}

void Player::changeState()
{
    // 根据速度翻转精灵
    if (velocity_.x < 0.0f)
    {
        idleAnim_->setFlip(SDL_FLIP_HORIZONTAL);
        moveAnim_->setFlip(SDL_FLIP_HORIZONTAL);
    }
    else if (velocity_.x > 0.0f)
    {
        idleAnim_->setFlip(SDL_FLIP_NONE);
        moveAnim_->setFlip(SDL_FLIP_NONE);
    }

    bool new_is_moving = glm::length(velocity_) > 0.1f;
    if (new_is_moving != is_moving_)
    { // 如果状态改变
        is_moving_ = new_is_moving;
        if (is_moving_)
        {
            idleAnim_->setActive(false);
            moveAnim_->setActive(true);
            // 让帧数保持一致
            moveAnim_->setFrameTimer(idleAnim_->getFrameTimer());
            moveAnim_->setCurrentFrame(idleAnim_->getCurrentFrame());
        }
        else
        {
            idleAnim_->setActive(true);
            moveAnim_->setActive(false);
            idleAnim_->setFrameTimer(moveAnim_->getFrameTimer());
            idleAnim_->setCurrentFrame(moveAnim_->getCurrentFrame());
        }
    }
}

void Player::whenDead()
{
    if (!stats_->getIsAlive()) {
        setActive(false);
        auto deadEffect = Effect::createEffectAddChild(nullptr, "assets/effect/1764.png", this->getPosition(), 2.0f);
        game_.getCurrentScene()->addChild(deadEffect);
        deadEffect = nullptr;
    }
}
