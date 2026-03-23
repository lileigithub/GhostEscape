#pragma once

#include "ObjectWord.h"

class Actor : public ObjectWord
{
protected:
    glm::vec2 velocity = glm::vec2();

public:
    Actor() = default;
    ~Actor() = default;
};