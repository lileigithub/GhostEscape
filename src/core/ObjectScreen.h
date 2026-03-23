#pragma once

#include "Object.h"

class ObjectScreen : public Object
{

protected:
    glm::vec2 screenPos_ = glm::vec2();

public:
    ObjectScreen() = default;
    ~ObjectScreen() = default;
};