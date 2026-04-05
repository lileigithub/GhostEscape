#include "hud_text.h"

HUDText *HUDText::createHUDTextAddChild(Object *parent, const std::string &text, glm::vec2 pos, glm::vec2 size, int fontSize, const std::string &bgPath, const std::string &fontPath, Anchor anchor)
{
    HUDText *hudText = new HUDText();
    hudText->init();
    hudText->setScreenPos(pos);
    hudText->setSpriteBg(Sprite::createSpriteAddChild<Sprite>(hudText, bgPath, 1, false, anchor));
    hudText->setSize(size);
    hudText->setTextLabel(TextLabel::createTextLabelAddChild(hudText, text, fontPath, fontSize, anchor));
    if (parent)
    {
        parent->addChild(hudText);
    }
    return hudText;
}

void HUDText::setBgSzieByText(float margin)
{
    if (sprite_bg_)
    {
        sprite_bg_->setSize(text_label_->getSize() + glm::vec2(margin, margin));
    }
}
