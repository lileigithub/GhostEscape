#include "ui_mouse.h"

UI_Mouse *UI_Mouse::createUiMouseAddChild(Object *parent, const std::string &path1, const std::string &path2, float scale, Anchor anchor)
{
    UI_Mouse *ui_mouse = new UI_Mouse();
    ui_mouse->init();
    ui_mouse->sprite1_ = Sprite::createSpriteAddChild<Sprite>(ui_mouse, path1, scale, false, anchor);
    ui_mouse->sprite2_ = Sprite::createSpriteAddChild<Sprite>(ui_mouse, path2, scale, false, anchor);
    ui_mouse->sprite1_->setActive(true);
    ui_mouse->sprite2_->setActive(false);
    if (parent != nullptr)
    {
        parent->addChild(ui_mouse);
    }
    return ui_mouse;
}

void UI_Mouse::update(float dt)
{
    ObjectScreen::update(dt);
    timer_ += dt;
    if (timer_ < 0.4f)
    {
        sprite1_->setActive(true);
        sprite2_->setActive(false);
    }
    else if (timer_ > 0.4f && timer_ < 0.9f)
    {
        sprite1_->setActive(false);
        sprite2_->setActive(true);
    }
    else
    {
        timer_ = 0.0f;
    }
    setScreenPos(game_.getMouseScreenPos());
}