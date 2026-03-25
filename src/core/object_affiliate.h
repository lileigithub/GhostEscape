#pragma once

#include "object_screen.h"
#include <glm/glm.hpp>

class ObjectAffiliate : public Object
{
    float scale_ = 1.0f;

protected:
    ObjectScreen *parent_ = nullptr;
    float offset_ = 0.0f;
    glm::vec2 size_{};

public:
    ObjectScreen *getParent() const { return parent_; }
    void setParent(ObjectScreen *parent) { parent_ = parent; }
    float getOffset() { return offset_; }
    void setOffset(float offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(glm::vec2 size) { size_ = size; }

    void setScale(float scale)
    {
        scale_ = scale;
        size_ *= scale;
    }
};