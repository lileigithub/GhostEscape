#include "sprite_anim.h"

void SpriteAnim::update(float dt)
{
    Sprite::update(dt);
    float frameTime = 1.0f / FPS_;
    frameTimer_ += dt;
    if (frameTimer_ >= frameTime)
    {
        if (++currentFrame_ == totalFrame_)
        {
            currentFrame_ = 0;
            if (!is_loop_)
            {
                SDL_Log("Animation finish");
                is_finish_ = true;
            }
        }
        frameTimer_ = 0.0f;
        imageTexture_->src_rect.x = currentFrame_ * imageTexture_->src_rect.h;
    }
}

void SpriteAnim::setImageTexture(ImageTexture *imageTexture)
{
    if (imageTexture != nullptr && imageTexture->texture != nullptr)
    {
        float w, h;
        if (!SDL_GetTextureSize(imageTexture->texture, &w, &h))
        {
            SDL_Log("error: Invalid texture detected");
            imageTexture = nullptr;
            return;
        }
    }
    imageTexture_ = imageTexture;
    totalFrame_ = static_cast<int>(imageTexture_->src_rect.w / imageTexture_->src_rect.h);
    SDL_Log("w : %f, h: %f, total frame: %d", imageTexture_->src_rect.w, imageTexture_->src_rect.h, totalFrame_);
    imageTexture_->src_rect.w = imageTexture_->src_rect.h;
    setSize(glm::vec2(imageTexture_->src_rect.w, imageTexture_->src_rect.h));
}
