#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Object.h"
class Scene : public Object
{
protected:
    glm::vec2 camera_pos_ = glm::vec2(0);
    std::vector<Object *> objects_;

public:
    Scene() = default;
    ~Scene() = default;
};