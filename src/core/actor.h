#pragma once

#include "object_world.h"
#include "../affiliates/affiliate_bar.h"

class Stats;
class Actor : public ObjectWorld
{
protected:
    glm::vec2 velocity_ = glm::vec2();
    float max_speed_ = 100.0f;
    bool is_moving_ = false;
    Stats *stats_ = nullptr;
    AffiliateBar *health_bar_ = nullptr;

public:
    void update(float dt) override;
    void move(float dt);
    float getDemage();
    Stats *getStats() { return stats_; }
    void updateHealthBar();
};