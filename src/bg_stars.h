#pragma once
#include "core/object.h"
class BgStars : public Object
{
protected:
    int stars_num_ = 0;
    std::vector<glm::vec2> stars_pos_near_;
    std::vector<glm::vec2> stars_pos_mid_;
    std::vector<glm::vec2> stars_pos_far_;

    SDL_FColor color_near_ = {0, 0, 0, 1};
    SDL_FColor color_mid_ = {0, 0, 0, 1};
    SDL_FColor color_far_ = {0, 0, 0, 1};

    float scale_near_ = 0.0f;
    float scale_mid_ = 0.0f;
    float scale_far_ = 0.0f;

    float color_timer_ = 0.0f;

public:
    static BgStars * createBgStarsAddChild(Object *parent, int stars_num, float scale_near, float scale_mid, float scale_far);
    void update(float dt) override;
    void render() override;

    void generateStarsPos();
};