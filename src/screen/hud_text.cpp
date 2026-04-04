#include "hud_text.h"

HUDText *HUDText::createHUDTextAddChild(Object *parent, const std::string &text, glm::vec2 pos, glm::vec2 size, const std::string &bgPath, const std::string &fontPath, int fontSize, Anchor anchor)
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