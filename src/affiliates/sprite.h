#pragma once

#include "../core/object_affiliate.h"
#include <glm/glm.hpp>
#include <string>

struct ImageTexture
{
    SDL_Texture *texture;
    SDL_FRect src_rect{};
    float angle = 0.0f;
    SDL_FlipMode flip_ = SDL_FLIP_NONE;

public:
    ImageTexture() = default;
    ImageTexture(const std::string &path);
};

class Sprite : public ObjectAffiliate
{
protected:
    ImageTexture *imageTexture_;

public:
    void render() override;
    void clean() override;
    virtual void setImageTexture(ImageTexture *imageTexture);
    template <typename T> static T *createSpriteAddChild(ObjectScreen *parent, const std::string &path, float scale, Anchor anchor = Anchor::CENTER);
    void setFlip(SDL_FlipMode flip) {imageTexture_->flip_ = flip;};
};

template <typename T> T *Sprite::createSpriteAddChild(ObjectScreen *parent, const std::string &path, float scale, Anchor anchor)
{
    ImageTexture *imageTexture = new ImageTexture(path);
    T *sprite = new T();
    sprite -> init();
    sprite->setImageTexture(imageTexture);
    sprite->setAnchor(anchor);
    sprite->setScale(scale);
    sprite->setParent(parent);
    parent->addChild(sprite);
    return sprite;
}