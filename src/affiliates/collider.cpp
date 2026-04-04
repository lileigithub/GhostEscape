#include "collider.h"

void Collider::render()
{
    ObjectAffiliate::render();
#ifdef DEBUG_MODE
    game_.renderFillCircle("assets/UI/circle.png", parent_->getScreenPos() + offset_, getSize(), 0.3f);
#endif
}

bool Collider::isColliding(Collider *other)
{
    // TODO 有bug，当技能在敌人的上方而没有包含敌人的最下边时，没有判断为碰撞
    if (other == nullptr)
        return false;
    if (type_ == CIRCLE && other->type_ == CIRCLE)
    {
        float distance = glm::length(parent_->getScreenPos() + offset_ - other->parent_->getScreenPos() - other->offset_);
        return distance <= (getSize().x + other->getSize().x) / 2.0f;
    }
    return false;
}

Collider *Collider::creatColliderAddChild(ObjectScreen *parent, glm::vec2 size, Type type, Anchor anchor)
{
    Collider *collider = new Collider();
    collider->init();
    collider->setParent(parent);
    collider->setAnchor(anchor);
    collider->setSize(size);
    collider->setType(type);
    parent->addChild(collider);
    return collider;
}
