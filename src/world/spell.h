#pragma once
#include "../affiliates/sprite_anim.h"
#include "../core/object_world.h"
#include <string>
#include <glm/glm.hpp>
class Spell : public ObjectWorld
{
protected:
    SpriteAnim *sprite_anim_ = nullptr;
    int damage_ = 120;
    int damage_min_frame_ = 0;
    int damage_max_frame_ = 0;

public:
    void update(float dt) override;
    void attack();
    static Spell* createSpellAddChild(Object* parent, const std::string& path, glm::vec2 pos, int damage, int damageMinFrame, int damageMaxFrame, float scale = 1.0f, Anchor anchor = CENTER);
    // getter setter
    int getDamage() { return damage_; }
    void setDamage(int damage) { damage_ = damage; }
};