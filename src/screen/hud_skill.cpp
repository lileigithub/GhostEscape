#include "hud_skill.h"
#include "glm/ext/vector_float2.hpp"

void HUDSkill::render()
{
  // 绘制背景
  SDL_SetTextureColorModFloat(icon_->getImageTexture()->texture, 0.3f, 0.3f, 0.3f);
  // 绘制图标 图标的位置等于父节点的位置加偏移量（sprite自己就是这么算的）
  auto pos = getScreenPos() + icon_->getOffset();
  game_.renderTexture(icon_->getImageTexture(), pos, icon_->getSize());
  SDL_SetTextureColorModFloat(icon_->getImageTexture()->texture, 1, 1, 1);
  // 然后再绘制其他的。
  ObjectScreen::render();
  // TODO 绘制冷却时间文字。
}

HUDSkill *HUDSkill::createHUDSkillAddChild(Object *parent,
                                           const std::string &path,
                                           glm::vec2 pos, float scale,
                                           Anchor anchor)
{
  HUDSkill *hudSkill = new HUDSkill();
  hudSkill->init();
  hudSkill->setScreenPos(pos);
  hudSkill->icon_ = Sprite::createSpriteAddChild<Sprite>(hudSkill, path, scale,
                                                         false, anchor);
  if (parent)
  {
    parent->addChild(hudSkill);
  }
  return hudSkill;
}

void HUDSkill::setPercent(float percent)
{
  percent_ = percent;
  if (icon_)
  {
    percent = glm::clamp(percent, 0.0f, 1.0f);
    icon_->setPercent({1.0f, percent});
  }
}