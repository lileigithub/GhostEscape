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
    if (imageTexture_ == nullptr || parent_ == nullptr || is_finish_ )
    {
        return;
    }
    game_.renderTexture(imageTexture_, parent_->getScreenPos() + offset_, getSize());
}

void Sprite::clean()
{
    ObjectAffiliate::clean();
}

void Sprite::setImageTexture(ImageTexture *imageTexture)
{
    imageTexture_ = imageTexture;
    setSize(glm::vec2(imageTexture_->src_rect.w, imageTexture_->src_rect.h));
}
