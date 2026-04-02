#include "hud_stats.h"
#include "../core/stats.h"
void HUDStats::init()
{
    ObjectScreen::init();
    health_bar_bg_ = Sprite::createSpriteAddChild<Sprite>(this, "assets/UI/bar_bg.png", 3.0f, false, Anchor::LEFT_CENTER);
    health_bar_bg_->setOffset(health_bar_bg_->getOffset() + glm::vec2(30.0f, 0.0f));
    health_bar_ = Sprite::createSpriteAddChild<Sprite>(this, "assets/UI/bar_red.png", 3.0f, false, Anchor::LEFT_CENTER);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(30.0f, 0.0f));
    health_bar_icon_ = Sprite::createSpriteAddChild<Sprite>(this, "assets/UI/Red Potion.png", 0.5f, false, Anchor::LEFT_CENTER);
    mana_bar_bg_ = Sprite::createSpriteAddChild<Sprite>(this, "assets/UI/bar_bg.png", 3.0f, false, Anchor::LEFT_CENTER);
    mana_bar_bg_->setOffset(mana_bar_bg_->getOffset() + glm::vec2(300.0f, 0.0f));
    mana_bar_ = Sprite::createSpriteAddChild<Sprite>(this, "assets/UI/bar_blue.png", 3.0f, false, Anchor::LEFT_CENTER);
    mana_bar_->setOffset(mana_bar_->getOffset() + glm::vec2(300.0f, 0.0f));
    mana_bar_icon_ = Sprite::createSpriteAddChild<Sprite>(this, "assets/UI/Blue Potion.png", 0.5f, false, Anchor::LEFT_CENTER);
    mana_bar_icon_->setOffset(mana_bar_icon_->getOffset() + glm::vec2(270.0f, 0.0f));
}

void HUDStats::update(float dt)
{
    ObjectScreen::update(dt);
    // 更新生命值bar
    if (health_bar_ && target_ && target_->getStats())
    {
        health_bar_->setPercent({target_->getStats()->getCurrentHealth() / target_->getStats()->getMaxHealth(), 1.0f});
    }
    // 更新魔法值bar
    if (mana_bar_ && target_ && target_->getStats())
    {
        mana_bar_->setPercent({target_->getStats()->getCurrentMana() / target_->getStats()->getMaxMana(), 1.0f});
        SDL_Log("mana bar curront:%d,  percent: %f", target_->getStats()->getCurrentMana(), mana_bar_->getPercent().x);
    }
}

HUDStats *HUDStats::createHUDStatsAddChild(Object *parent, Actor *target, glm::vec2 pos)
{
    HUDStats *hud_stats = new HUDStats();
    hud_stats->init();
    hud_stats->target_ = target;
    hud_stats->screen_pos_ = pos;
    if (parent)
    {
        parent->addChild(hud_stats);
    }
    return hud_stats;
}
