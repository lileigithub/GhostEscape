#pragma once

#include "../affiliates/sprite.h"
#include "../core/object_screen.h"
class HUDButton : public ObjectScreen
{
protected:
    Sprite *normal_sprite_ = nullptr;
    Sprite *hover_sprite_ = nullptr;
    Sprite *pressed_sprite_ = nullptr;

    bool is_hover_ = false;   // 鼠标悬停
    bool is_pressed_ = false;   // 鼠标按下
    bool is_trigger_ = false; // 是否触发按钮
    bool is_freezed_ = false; // 是否冻结
public:
    bool handleEvents(SDL_Event &event) override;
    void update(float dt) override;
    void render() override;

    static HUDButton *createHUDButtonAddChild(Object* parent, glm::vec2 pos, const std::string &normal_file_path, 
                                            const std::string &hover_file_path, const std::string &pressed_file_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    void checkHover();
    void changeSpriteState();
    bool getResetTrigger();
    bool setFreezed(bool is_freezed) { is_freezed_ = is_freezed; return is_freezed_; }
};