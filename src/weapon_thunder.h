#pragma once
#include "core/weapon.h"
#include "screen/hud_skill.h"
class WeaponThunder : public Weapon
{
    protected:
    HUDSkill *hud_skill_ = nullptr;
    float demage_ = 50.0f;
public:
    void init() override;
    void update(float dt) override;
    static WeaponThunder *createWeaponThunderAddChild(Actor *parent, float cooldownTime = 1.0f, int costMana = 20);
    bool handleEvents(SDL_Event &) override;
};