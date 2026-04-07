#pragma once
#include "../affiliates/collider.h"
#include "object_screen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    Collider *collider_ = nullptr;

private:
    glm::vec2 position_ = glm::vec2();

public:
    void init() override { object_type_ = ObjectType::WORLD; };
    void update(float dt) override;

    void setPosition(const glm::vec2 &position);
    void setScreenPos(const glm::vec2 &screenPos);
    glm::vec2 getPosition() const override
    {
        return position_;
    }
    Collider* getCollider() { return collider_; }
};