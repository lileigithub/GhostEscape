#pragma once
#include "../core/object_affiliate.h"
#include <string>
class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text *ttf_text_ = nullptr;
    int font_size_ = 16;
    std::string font_path_;

public:

    void render() override;
    void clean() override;

    static TextLabel *createTextLabelAddChild(ObjectScreen *parent, const std::string &text, const std::string &fontPath, int fontSize, Anchor anchor);

    // getters and setters
    void setFont(const std::string &fontPath, int fontSize);
    void setFontSize(int fontSize);
    int getFontSize() { return font_size_; }
    void setFontPath(const std::string &fontPath);
    std::string getFontPath() { return font_path_; }

    void setText(const std::string &text) {TTF_SetTextString(ttf_text_, text.c_str(), 0);};
    std::string getText() { return ttf_text_->text; };

    private:
    void updateSize();
};