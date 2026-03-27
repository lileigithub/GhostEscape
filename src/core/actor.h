#pragma once

#include "object_world.h"

class Stats;
class Actor : public ObjectWord
{
protected:
    glm::vec2 velocity_ = glm::vec2();
    float max_speed_ = 100.0f;
    bool is_moving_ = false;
    Stats* stats_ = nullptr;
public:
    void move(float dt);
    int getDemage();
};