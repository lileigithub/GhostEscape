#include "collider.h"

void Collider::render()
{
    ObjectAffiliate::render();
#ifdef DEBUG_MODE
    game_.renderFillCircle("assets/UI/circle.png", parent_->getScreenPos() + offset_, size_, 0.3f);
#endif
}

bool Collider::isColliding(Collider *other)
{
    if (other == nullptr)
        return false;
    if (type_ == CIRCLE && other->type_ == CIRCLE)
    {
        float distance = glm::length(parent_->getPosition() + offset_ - other->parent_->getPosition() - other->offset_);
        return distance < (size_.x + other->size_.x) / 2;
    }
    return false;
}

Collider *Collider::creatColliderAddChild(ObjectScreen *parent, glm::vec2 size, glm::vec2 offset, Type type)
{
    Collider *collider = new Collider();
    collider->init();
    collider->setParent(parent);
    collider->setSize(size);
    collider->setOffset(offset);
    collider->setType(type);
    parent->addChild(collider);
    return collider;
}
