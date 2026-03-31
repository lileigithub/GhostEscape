#include "weapon.h"
#include "actor.h"
#include "stats.h"
#include "scene.h"

void Weapon::update(float dt)
{
    Object::update(dt);
    cooldown_timer_ += dt;
}

void Weapon::attack(Spell *spell)
{
    if (spell != nullptr && parent_ != nullptr) {
        SDL_Log("cooldown_timer_: %f, mana: %d", cooldown_timer_, parent_->getStats()->getCurrentMana());
        cooldown_timer_ = 0.0f;
        parent_->getStats()->useMana(cost_mana_);
        game_.getCurrentScene()->addChild(spell);
    }
}

bool Weapon::canAttack()
{
    if (parent_ != nullptr && cooldown_timer_ >= cooldown_time_ && parent_->getStats()->canUseMana(cost_mana_)) {
        return true;
    }
    return false;
}
