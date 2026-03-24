#pragma once
#include "object_screen.h"

class ObjectWord : public ObjectScreen
{
private:
    glm::vec2 position_ = glm::vec2();

public:
    void init() override { object_type_ = ObjectType::WORLD; };
    virtual void update(float dt) override;

    void setPosition(const glm::vec2 &position);

    void setScreenPos(const glm::vec2 &screenPos);

    glm::vec2 getPosition() const
    {
        return position_;
    }
};