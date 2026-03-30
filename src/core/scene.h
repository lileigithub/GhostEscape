#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "object.h"
#include "object_screen.h"
#include "object_world.h"

class Scene : public Object
{
    std::vector<Object *> sceen_need_add_children_;
protected:
    glm::vec2 wordSize_ = glm::vec2();
    glm::vec2 cameraPos_ = glm::vec2();
    // 为了分层渲染，所以给Object分类
    std::vector<ObjectWorld *> children_world_;
    std::vector<ObjectScreen *> children_screen_;

public:
    void handleEvents(SDL_Event &) override;
    void update(float) override;
    void render() override;
    void clean() override;

    void addChild(Object *child) override;
    void removeChild(Object *child) override;

    void setCameraPos(glm::vec2 cameraPos);
    glm::vec2 getCameraPos() const { return cameraPos_; }
    glm::vec2 getWordSize() const { return wordSize_; }
    void setWordSize(glm::vec2 wordSize) { wordSize_ = wordSize; }
    glm::vec2 wordPosToScreenPos(glm::vec2 wordPos);
    glm::vec2 screenPosToWorldPos(glm::vec2 screenPos);
    std::vector<ObjectWorld *> *getChildrenWorld() { return &children_world_; }
    std::vector<ObjectScreen *> *getChildrenScreen() { return &children_screen_; }
};