#pragma once
#include "../core/object_world.h"
#include "../affiliates/sprite_anim.h"
#include <string>
class Effect : public ObjectWorld
{
protected:
    SpriteAnim *spriteAnim_ = nullptr;
    Object *nextObject_ = nullptr;

public:
    void update(float dt) override;
    static Effect *createEffectAddChild(Object *parent, const std::string &path, glm::vec2 pos, float scale = 1.0f, Object *nextObject = nullptr);
    void setSpriteAnim(SpriteAnim *spriteAnim) { spriteAnim_ = spriteAnim; }
    SpriteAnim *getSpriteAnim() { return spriteAnim_; }

    void whenFinish();
};