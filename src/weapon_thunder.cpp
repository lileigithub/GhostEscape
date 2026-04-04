#include "weapon_thunder.h"
#include "core/actor.h"
#include "core/stats.h"
#include "core/scene.h"

void WeaponThunder::init()
{
    Weapon::init();
    hud_skill_ = HUDSkill::createHUDSkillAddChild(game_.getCurrentScene(), "assets/UI/Electric-Icon.png", {game_.getSceneSize().x - 300.0f, 30.0f}, 0.14f, CENTER);
}

void WeaponThunder::update(float dt)
{
    Weapon::update(dt);
    if (hud_skill_) {
        hud_skill_-> setPercent(cooldown_timer_ / cooldown_time_);
    }
}

WeaponThunder *WeaponThunder::createWeaponThunderAddChild(Actor *parent, float cooldownTime, int costMana)
{
    WeaponThunder *weaponThunder = new WeaponThunder();
    weaponThunder->init();
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
            game_.playChunk("assets/sound/big-thunder.mp3");
            auto pos = game_.getMousePos();
            auto spell = Spell::createSpellAddChild(nullptr, "assets/effect/Thunderstrike w blur.png", pos, demage_, 5, 9, 3.0f);
            attack(spell);
        }
    }
}
