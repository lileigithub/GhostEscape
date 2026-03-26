#pragma once

#include "object_screen.h"
#include <glm/glm.hpp>

class ObjectAffiliate : public Object
{
    float scale_ = 1.0f;

protected:
    ObjectScreen *parent_ = nullptr;
    glm::vec2 offset_{};
    glm::vec2 size_{};

public:
    ObjectScreen *getParent() const { return parent_; }
    void setParent(ObjectScreen *parent) { parent_ = parent; }
    glm::vec2 getOffset() { return offset_; }
    void setOffset(glm::vec2 offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(glm::vec2 size) { size_ = size; }

    void setScale(float scale)
    {
        scale_ = scale;
        size_ *= scale;
    }
};