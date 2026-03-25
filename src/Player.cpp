#include "player.h"
#include "core/scene.h"
#include "affiliates/sprite.h"

void Player::init()
{
    maxSpeed_ = 500.f;
    setPosition(game_.getCurrentScene()->getWordSize() / 2.0f);
    ImageTexture *imageTexture = new ImageTexture("assets/sprite/ghost-idle.png");
    Sprite *sprite = new Sprite();
    sprite->setImageTexture(imageTexture);
    sprite->setParent(this);
    addChild(sprite);
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
    Actor::render();
    //game_.drawRect({screen_pos_.x - 20, screen_pos_.y - 20, 40, 40}, {255, 255, 255, 255});
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
