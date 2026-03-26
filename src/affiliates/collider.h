#pragma once
#include "../core/object_affiliate.h"

class Collider : public ObjectAffiliate
{
public:
    enum Type
    {
        CIRCLE,
        RECTANGLE
    };

protected:
    Type type_;
    SDL_Texture *texture_;

public:
    void render() override;
    bool isColliding(Collider *other);
    static Collider *creatColliderAddChild(ObjectScreen *parent, glm::vec2 size, glm::vec2 offset, Type type = CIRCLE);

    void setType(Type type) { type_ = type; }
    Type getType() { return type_; }
};