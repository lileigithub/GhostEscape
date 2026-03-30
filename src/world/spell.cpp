#include "spell.h"
#include "../core/scene.h"
void Spell::update(float dt)
{
    ObjectWorld::update(dt);
    attack();
    if (sprite_anim_->getIsFinish())
    {
        need_remove_ = true;
    }
}

void Spell::attack()
{
    std::vector<ObjectWorld *> *worldChildren = game_.getCurrentScene()->getChildrenWorld();
    for (auto it : *worldChildren)
    {
        if (it->getObjectType() == ObjectType::ENEMY)
        {
            if (it->getCollider() && it->getCollider()->isColliding(this->getCollider()) 
            && (this->sprite_anim_->getCurrentFrame() >= damage_min_frame_ && this->sprite_anim_->getCurrentFrame() <= damage_max_frame_))
            {
                it->takeDamage(damage_);
            }
        }
    }
}

Spell *Spell::createSpellAddChild(Object *parent, const std::string &path, glm::vec2 pos, int damage, int damageMinFrame, int damageMaxFrame, float scale, Anchor anchor)
{
    Spell *spell = new Spell();
    spell->setPosition(pos);
    spell->setDamage(damage);
    spell->damage_min_frame_ = damageMinFrame;
    spell->damage_max_frame_ = damageMaxFrame;
    spell->sprite_anim_ = Sprite::createSpriteAddChild<SpriteAnim>(spell, path, scale, false, anchor);
    spell->collider_ = Collider::creatColliderAddChild(spell, spell->sprite_anim_->getSize());
    if (parent != nullptr)
    {
        parent->addChild(spell);
    }
    return spell;
}
