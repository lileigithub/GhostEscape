#pragma once

#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 screenPos_ = glm::vec2();

public:
    void init() override {object_type_ = ObjectType::SCREEN;};
};