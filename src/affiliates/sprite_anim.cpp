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
            if (!is_loop_) {
                is_active_ = false;
            }
        }
        frameTimer_ = 0.0f;
        imageTexture_->src_rect.x = currentFrame_ * imageTexture_->src_rect.h;
    }
}

void SpriteAnim::setImageTexture(ImageTexture *imageTexture)
{
    imageTexture_ = imageTexture;
    totalFrame_ = static_cast<int>(imageTexture_->src_rect.w / imageTexture_->src_rect.h);
    imageTexture_->src_rect.w = imageTexture_->src_rect.h;
    size_ = glm::vec2(imageTexture_->src_rect.w, imageTexture_->src_rect.h);
}
