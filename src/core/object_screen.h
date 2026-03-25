#pragma once

#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 screen_pos_ = glm::vec2();

public:
    void init() override {object_type_ = ObjectType::SCREEN;};
    glm::vec2 getScreenPos() const {return screen_pos_;}
};