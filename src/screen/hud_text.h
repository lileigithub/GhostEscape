#pragma once

#include "../affiliates/sprite.h"
#include "../affiliates/text_label.h"
#include "../core/object_screen.h"
class HUDText : public ObjectScreen
{
protected:
    Sprite *sprite_bg_ = nullptr;
    TextLabel *text_label_ = nullptr;
    glm::vec2 size_;

public:
    static HUDText *createHUDTextAddChild(Object *parent, const std::string &text, glm::vec2 pos, glm::vec2 size, int fontSize = 16,
                                          const std::string &bgPath = "assets/UI/Textfield_01.png", const std::string &fontPath = "assets/font/VonwaonBitmap-16px.ttf",
                                          Anchor anchor = Anchor::CENTER);

    // getters and setters
    Sprite *getSpriteBg() const { return sprite_bg_; }
    void setSpriteBg(Sprite *spriteBg) { sprite_bg_ = spriteBg; }
    TextLabel *getTextLabel() const { return text_label_; }
    void setTextLabel(TextLabel *textLabel) { text_label_ = textLabel; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2 &size)
    {
        size_ = size;
        sprite_bg_->setSize(size);
    }
    void setText(const std::string &text) { text_label_->setText(text); }
};