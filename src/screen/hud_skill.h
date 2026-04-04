#pragma once
#include "../affiliates/sprite.h"
#include "../core/object_screen.h"

class HUDSkill : public ObjectScreen
{
protected:
  Sprite *icon_ = nullptr;
  float percent_ = 1.0f;

public:
  void render() override;

  static HUDSkill *createHUDSkillAddChild(Object *parent, const std::string &path, glm::vec2 pos, float scale = 1.0f, Anchor anchor = CENTER);
  void setPercent(float percent);
  float getPercent() { return percent_; }
};