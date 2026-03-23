#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Object.h"

class Scene : public Object
{
private:
    std::vector<Object *> objects_;
    glm::vec2 cameraPos_ = glm::vec2();
    glm::vec2 wordSize_ = glm::vec2();

public:
    Scene() = default;
    ~Scene() = default;

    void setCameraPos(glm::vec2 cameraPos);
    glm::vec2 getCameraPos() const { return cameraPos_; }
    glm::vec2 getWordSize() const { return wordSize_; }
    void setWordSize(glm::vec2 wordSize) { wordSize_ = wordSize; }
    glm::vec2 wordPosToScreenPos(glm::vec2 wordPos);
    glm::vec2 screenPosToWorldPos(glm::vec2 screenPos);
};