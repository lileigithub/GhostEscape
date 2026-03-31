#include "affiliate_bar.h"

AffiliateBar *AffiliateBar::createAffiliateBarAddChild(ObjectScreen *parent, glm::vec2 size, Anchor anchor)
{
    AffiliateBar *bar = new AffiliateBar();
    bar->setAnchor(anchor);
    bar->setSize(size);
    if (parent != nullptr)
    {
        bar->parent_ = parent;
        bar->parent_->addChild(bar);
    }
    return bar;
}

void AffiliateBar::render()
{
    ObjectAffiliate::render();
    if (parent_ == nullptr)
        return;

    SDL_FColor renderColor;
    if (percent_ <= 0.3f)
    {
        renderColor = red_;
    }
    else if (percent_ > 0.3f && percent_ <= 0.6f)
    {
        renderColor = yellow_;
    }
    else
    {
        renderColor = green_;
    }
    SDL_SetRenderDrawColorFloat(game_.getRenderer(), renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    ObjectAffiliate::render();
    SDL_FRect rect = {parent_->getScreenPos().x + offset_.x, parent_->getScreenPos().y + offset_.y, getSize().x, getSize().y};
    SDL_FRect rectFill = {parent_->getScreenPos().x + offset_.x, parent_->getScreenPos().y + offset_.y, getSize().x * percent_, getSize().y};
    SDL_RenderRect(game_.getRenderer(), &rect);
    SDL_RenderFillRect(game_.getRenderer(), &rectFill);
    SDL_SetRenderDrawColorFloat(game_.getRenderer(), 0, 0, 0, 0);
}