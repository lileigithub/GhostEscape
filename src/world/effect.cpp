#include "effect.h"
#include "../core/scene.h"

void Effect::update(float dt)
{
    ObjectWorld::update(dt);
    whenFinish();
}

Effect *Effect::createEffectAddChild(Object *parent, const std::string &path, glm::vec2 pos, float scale, Object *nextObject)
{
    Effect *effect = new Effect();
    effect->init();
    effect->spriteAnim_ = Sprite::createSpriteAddChild<SpriteAnim>(effect, path, scale, false);
    effect->nextObject_ = nextObject;
    effect->setPosition(pos);
    if (parent != nullptr)
    {
        SDL_Log("effect add scene");
        parent->addChild(effect);
    }
    return effect;
}

void Effect::whenFinish()
{
    if (spriteAnim_->getIsFinish())
    {
        need_remove_ = true;
        if (nextObject_)
        {
            game_.getCurrentScene()->safeAddChild(nextObject_);
            nextObject_ = nullptr;
        }
    }
}
