#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Object.h"
class Scene : public Object
{
protected:
    glm::vec2 camera_position_ = glm::vec2();
    std::vector<Object *> objects_;

public:
    Scene() = default;
    ~Scene() = default;

    void init() override {};
    void handleEvents(SDL_Event &) override {};
    void update(float) override {};
    void render() override {};
    void clean() override {};
};