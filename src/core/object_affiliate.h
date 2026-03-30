#pragma once

#include "object_screen.h"
#include <glm/glm.hpp>

class ObjectAffiliate : public Object
{
    glm::vec2 size_{};
    float scale_ = 1.0f;

protected:
    ObjectScreen *parent_ = nullptr;
    glm::vec2 offset_{};
    Anchor anchor_ = CENTER;

public:
    void resetOffsetByAnchor(Anchor anchor);
    ObjectScreen *getParent() const { return parent_; }
    void setParent(ObjectScreen *parent) { parent_ = parent; }
    glm::vec2 getOffset() { return offset_; }
    void setOffset(glm::vec2 offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(glm::vec2 size);
    Anchor getAnchor() const { return anchor_; }
    void setAnchor(Anchor anchor) { anchor_ = anchor; }

    void setScale(float scale);
};