#pragma once

#include <glm/glm.hpp>
#include <string>
#include "../core/object_affiliate.h"

struct ImageTexture
{
    SDL_Texture *texture;
    SDL_FRect src_rect{};
    float angle = 0.0f;
    SDL_FlipMode flip = SDL_FLIP_NONE;

public:
    ImageTexture() = default;
    ImageTexture(const std::string &path);
};

class Sprite : public ObjectAffiliate
{
    ImageTexture *imageTexture_;

public:
    void render() override;
    void clean() override;
    void setImageTexture(ImageTexture *imageTexture);
};