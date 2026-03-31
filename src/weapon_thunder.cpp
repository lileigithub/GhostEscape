#include "weapon_thunder.h"
#include "core/actor.h"
#include "core/stats.h"
WeaponThunder *WeaponThunder::createWeaponThunderAddChild(Actor *parent, float cooldownTime, int costMana)
{
    WeaponThunder *weaponThunder = new WeaponThunder();
    weaponThunder->cooldown_time_ = cooldownTime;
    weaponThunder->cost_mana_ = costMana;
    weaponThunder->parent_ = parent;
    parent->addChild(weaponThunder);
    return weaponThunder;
}

void WeaponThunder::handleEvents(SDL_Event &event)
{
    Weapon::handleEvents(event);
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT && canAttack())
        {
            // 施放技能
            auto pos = game_.getMousePos();
            parent_->getStats()->useMana(cost_mana_);
            auto spell = Spell::createSpellAddChild(nullptr, "assets/effect/Thunderstrike w blur.png", pos, 50, 5, 9, 3.0f);
            attack(spell);
        }
    }
}
