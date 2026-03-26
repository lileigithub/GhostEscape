#include "object_affiliate.h"

void ObjectAffiliate::resetOffsetByAnchor(Anchor anchor)
{
    anchor_ = anchor;
    switch (anchor)
    {
    case CENTER:
        offset_ = -size_ / 2.0f;
        break;
    case TOP_LEFT:
        offset_.x = 0.0f;
        offset_.y = 0.0f;
        break;
    case TOP_CENTER:
        offset_.x = -size_.x / 2.0f;
        offset_.y = 0.0f;
        break;
    case TOP_RIGHT:
        offset_.x = -size_.x;
        offset_.y = 0.0f;
        break;
    case LEFT_CENTER:
        offset_.x = 0.0f;
        offset_.y = -size_.y / 2.0f;
        break;
    case RIGHT_CENTER:
        offset_.x = -size_.x;
        offset_.y = -size_.y / 2.0f;
        break;
    case BOTTOM_LEFT:
        offset_.x = 0.0f;
        offset_.y = -size_.y;
        break;
    case BOTTOM_CENTER:
        offset_.x = -size_.x / 2.0f;
        offset_.y = -size_.y;
        break;
    case BOTTOM_RIGHT:
        offset_.x = -size_.x;
        offset_.y = -size_.y;
        break;
    default:
        break;
    }
}

void ObjectAffiliate::setSize(glm::vec2 size)
{
    size_ = size;
    resetOffsetByAnchor(anchor_);
}

void ObjectAffiliate::setScale(float scale)
{
    scale_ = scale;
    size_ *= scale;
    resetOffsetByAnchor(anchor_);
}
