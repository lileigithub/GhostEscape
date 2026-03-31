#pragma once
#include "../core/object_affiliate.h"
class AffiliateBar : public ObjectAffiliate
{

protected:
    float percent_ = 1.0f;
    

    SDL_FColor red_ = {1.0f, 0, 0, 0};
    SDL_FColor green_ = {0, 1.0f, 0, 0};
    SDL_FColor yellow_ = {1, 0.65f, 0, 0};

public:
    static AffiliateBar *createAffiliateBarAddChild(ObjectScreen *parent, glm::vec2 size, Anchor anchor);
    void render() override;

    // setters and getters
    void setPercent(float percent) { percent_ = percent; }
    float getPercent() { return percent_; }
};