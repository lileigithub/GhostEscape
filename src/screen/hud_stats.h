#pragma once
#include "../core/object_screen.h"
#include "../affiliates/sprite.h"
#include "../core/actor.h"
class HUDStats : public ObjectScreen
{

protected:
    Sprite *health_bar_ = nullptr;
    Sprite *health_bar_bg_ = nullptr;
    Sprite *health_bar_icon_ = nullptr;
    Sprite *mana_bar_ = nullptr;
    Sprite *mana_bar_bg_ = nullptr;
    Sprite *mana_bar_icon_ = nullptr;

    Actor *target_ = nullptr;

public:
    void init() override;
    void update(float dt) override;

    static HUDStats * createHUDStatsAddChild(Object *parent, Actor *target, glm::vec2 pos);
};