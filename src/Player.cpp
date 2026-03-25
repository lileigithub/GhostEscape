#include "player.h"
#include "affiliates/sprite_anim.h"
#include "core/scene.h"

void Player::init()
{
    maxSpeed_ = 500.f;
    setPosition(game_.getCurrentScene()->getWordSize() / 2.0f);
    Sprite::createSpriteAddChild<SpriteAnim>(this, "assets/sprite/ghost-idle.png", 2.0f);
};
void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}
void Player::update(float dt)
{
    Actor::update(dt);
    keyBoardControl();
    move(dt);
}
void Player::render()
{
    game_.drawRect({getScreenPos().x, getScreenPos().y, 10.0f, 10.0f}, {255, 255, 255, 255});
    Actor::render();
}
void Player::clean()
{
    Actor::clean();
}
void Player::keyBoardControl()
{
    velocity *= 0.9f;

    float xSpeedVelocity = 0.0f;
    float ySpeedVelocity = 0.0f;

    auto keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP])
    {
        ySpeedVelocity -= maxSpeed_;
    }
    if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN])
    {
        ySpeedVelocity += maxSpeed_;
    }
    if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT])
    {
        xSpeedVelocity -= maxSpeed_;
    }
    if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT])
    {
        xSpeedVelocity += maxSpeed_;
    }
    velocity.x = xSpeedVelocity;
    velocity.y = ySpeedVelocity;
}

void Player::move(float deltaTime)
{
    setPosition(glm::clamp(getPosition() + velocity * deltaTime, glm::vec2(), game_.getCurrentScene()->getWordSize()));
}
