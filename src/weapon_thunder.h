#pragma once
#include "core/weapon.h"
#include <string>
class WeaponThunder : public Weapon
{
public:
    static WeaponThunder *createWeaponThunderAddChild(Actor *parent, float cooldownTime = 1.0f, int costMana = 20);
    void handleEvents(SDL_Event &) override;
};