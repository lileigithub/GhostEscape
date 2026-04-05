#include "hud_button.h"

void HUDButton::handleEvents(SDL_Event &event)
{
    ObjectScreen::handleEvents(event);
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (is_hover_)
            {
                is_pressed_ = true;
                game_.playChunk("assets/sound/UI_button12.wav");
            }
        }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (is_pressed_)
            {
                is_pressed_ = false;
                if (is_hover_)
                {
                    // 在按钮内松开鼠标，触发事件
                    is_trigger_ = true;
                }
            }
        }
    }
}

void HUDButton::update(float dt)
{
    ObjectScreen::update(dt);
    checkHover();
    changeSpriteState();
}

HUDButton *HUDButton::createHUDButtonAddChild(Object *parent, glm::vec2 screen_pos, const std::string &normal_file_path,
                                              const std::string &hover_file_path, const std::string &pressed_file_path, float scale, Anchor anchor)
{
    HUDButton *button = new HUDButton();
    button->init();
    button->setScreenPos(screen_pos);
    button->normal_sprite_ = Sprite::createSpriteAddChild<Sprite>(button, normal_file_path, scale, false, anchor);
    button->hover_sprite_ = Sprite::createSpriteAddChild<Sprite>(button, hover_file_path, scale, false, anchor);
    button->pressed_sprite_ = Sprite::createSpriteAddChild<Sprite>(button, pressed_file_path, scale, false, anchor);
    if (parent)
    {
        parent->addChild(button);
    }
    return button;
}

void HUDButton::checkHover()
{
    // 鼠标位置是否在按钮内
    auto pos = getScreenPos() + normal_sprite_->getOffset();
    bool new_is_hover_ = game_.checkPointInRect(game_.getMousePos(), pos, pos + normal_sprite_->getSize());
    if (new_is_hover_ != is_hover_)
    {
        is_hover_ = new_is_hover_;
        if (is_hover_) game_.playChunk("assets/sound/UI_button08.wav");// 状态改变，并且是从未悬停到悬停，播放悬停音效
    }
    
}

void HUDButton::changeSpriteState()
{
    if (!is_hover_ && !is_pressed_)
    { // 按钮未按下且鼠标未悬停 普通状态
        normal_sprite_->setActive(true);
        hover_sprite_->setActive(false);
        pressed_sprite_->setActive(false);
    }
    else if (is_hover_ && !is_pressed_)
    { // 按钮未按下且鼠标悬停 悬停状态
        normal_sprite_->setActive(false);
        hover_sprite_->setActive(true);
        pressed_sprite_->setActive(false);
    }
    else
    { // 其他情况 按下状态
        normal_sprite_->setActive(false);
        hover_sprite_->setActive(false);
        pressed_sprite_->setActive(true);
    }
}

bool HUDButton::getResetTrigger()
{
    if (is_trigger_)
    {
        is_trigger_ = false;
        return true;
    }
    return false;
}
