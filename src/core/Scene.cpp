#include "scene.h"

glm::vec2 Scene::wordPosToScreenPos(glm::vec2 wordPos)
{
    return wordPos - cameraPos_;
}

glm::vec2 Scene::screenPosToWorldPos(glm::vec2 screenPos)
{
    return screenPos + cameraPos_;
}

void Scene::setCameraPos(glm::vec2 cameraPos)
{
    cameraPos_ = glm::clamp(cameraPos, glm::vec2(-30.0f, -30.0f) , wordSize_ - game.getSceneSize() + 30.0f);
}
