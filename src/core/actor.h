#pragma once

#include "object_world.h"

class Actor : public ObjectWord
{
protected:
    glm::vec2 velocity_ = glm::vec2();
    float max_speed_ = 100.0f;
    bool is_moving_ = false;
public:
    void move(float dt);
};