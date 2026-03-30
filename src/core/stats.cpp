#include "stats.h"
#include "actor.h"
void Stats::update(float dt)
{
    if (is_invicible_)
    {
        if (invicible_timer_ >= invicible_time_)
        {
            invicible_timer_ = 0.0f;
            is_invicible_ = false;
        } else {
            invicible_timer_ += dt;
        }
    }
}
void Stats::takeDamage(int demage)
{
    if (is_alive_ == false) return;
    if (invicible_timer_ > FLT_EPSILON)
        return;
    if (demage < 0)
    {
        return;
    }
    current_health_ -= demage;
    is_invicible_ = true;
    SDL_Log("health: %d", current_health_);
    if (current_health_ <= 0)
    {
        current_health_ = 0;
        is_alive_ = false;
    }
}

Stats *Stats::createStatsAddChild(Actor *parent, int health, int mana, int demage)
{
    Stats *stats = new Stats();
    stats->parent_ = parent;
    stats->current_health_ = health;
    stats->current_mana_ = mana;
    stats->demage_ = demage;
    stats->parent_->addChild(stats);
    return stats;
}
