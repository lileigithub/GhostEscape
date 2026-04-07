#include "text_label.h"

void TextLabel::render()
{
    ObjectAffiliate::render();
    if (ttf_text_)
    {
        auto pos = parent_->getScreenPos() + getOffset();
        TTF_DrawRendererText(ttf_text_, pos.x, pos.y);
    }
}

void TextLabel::clean()
{
    ObjectAffiliate::clean();
    if (ttf_text_)
    {
        TTF_DestroyText(ttf_text_);
        ttf_text_ = nullptr;
    }
}

TextLabel *TextLabel::createTextLabelAddChild(ObjectScreen *parent, const std::string &text, const std::string &fontPath, float fontSize, Anchor anchor)
{
    TextLabel *textlabel = new TextLabel();
    textlabel->init();
    textlabel->setFont(fontPath, fontSize);
    textlabel->setText(text);
    textlabel->setAnchor(anchor);
    textlabel->updateSize();
    if (parent)
    {
        textlabel->parent_ = parent;
        parent->addChild(textlabel);
    }
    return textlabel;
}

void TextLabel::setFont(const std::string &fontPath, float fontSize)
{
    font_size_ = fontSize;
    font_path_ = fontPath;
    if (!ttf_text_)
    {
        ttf_text_ = game_.createTTF_Text("", fontPath, fontSize);
    }
    else
    {
        auto font = game_.getAssetStore()->getFont(fontPath, fontSize);
        TTF_SetTextFont(ttf_text_, font);
    }
    updateSize();
}

void TextLabel::setFontSize(float fontSize)
{
    font_size_ = fontSize;
    auto font = game_.getAssetStore()->getFont(font_path_, fontSize);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setFontPath(const std::string &fontPath)
{
    font_path_ = fontPath;
    auto font = game_.getAssetStore()->getFont(fontPath, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::updateSize()
{
    int w, h;
    TTF_GetTextSize(ttf_text_, &w, &h);
    setSize({w, h});
}
