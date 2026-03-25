#include "sprite.h"
#include "../core/game.h"

ImageTexture::ImageTexture(const std::string &path)
{
    texture = Game::getInstance().getAssetStore()->getImmage(path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

void Sprite::render()
{
    ObjectAffiliate::render();
    if (imageTexture_ == nullptr)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Texture is null");
        return;
    }
    if (parent_ == nullptr)
    {
        return;
    }
    game_.renderTexture(imageTexture_, parent_->getScreenPos() + offset_, size_);
}

void Sprite::clean()
{
    ObjectAffiliate::clean();
    SDL_DestroyTexture(imageTexture_->texture);
}

void Sprite::setImageTexture(ImageTexture *imageTexture)
{
    size_ = glm::vec2(imageTexture->src_rect.w, imageTexture->src_rect.h);
    imageTexture_ = imageTexture;
}
