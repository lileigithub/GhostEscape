#pragma once
#include "../affiliates/sprite.h"
#include "../core/object_screen.h"
#include "../core/object_affiliate.h"

class UI_Mouse : ObjectScreen
{
protected:
    Sprite *sprite1_ = nullptr;
    Sprite *sprite2_ = nullptr;
    SDL_MouseButtonFlags mouseButtonFlags_;
    float timer_ = 0.0f;
public:
    static UI_Mouse * createUiMouseAddChild(Object * parent, const std::string &path1, const std::string &path2, float scale = 1.0f, ObjectAffiliate::Anchor anchor = ObjectAffiliate::Anchor::CENTER);
    void update(float dt) override;
};