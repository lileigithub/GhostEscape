#pragma once

#include "sprite.h"

class SpriteAnim : public Sprite
{

protected:
    int currentFrame_ = 0;
    int totalFrame_ = 0;
    int FPS_ = 10;
    float frameTimer_ = 0.0f;
    bool is_loop_ = true;

public:
    void update(float dt) override;

    void setImageTexture(ImageTexture *imageTexture) override;
    void setLoop(bool loop) override { is_loop_ = loop; }

    int getCurrentFrame() { return currentFrame_; }
    void setCurrentFrame(int frame) { currentFrame_ = frame; }
    int getTotalFrame() { return totalFrame_; }
    void setTotalFrame(int frame) { totalFrame_ = frame; }
    int getFPS() { return FPS_; }
    void setFPS(int fps) { FPS_ = fps; }
    float getFrameTimer() { return frameTimer_; }
    void setFrameTimer(float timer) { frameTimer_ = timer; }
};