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
    cameraPos_ = glm::clamp(cameraPos, glm::vec2(-30.0f, -30.0f), wordSize_ - game_.getSceneSize() + 30.0f);
}

void Scene::handleEvents(SDL_Event &event)
{
    Object::handleEvents(event);
    for (auto child : children_world_)
    {
        child->handleEvents(event);
    }
    for (auto child : children_screen_)
    {
        child->handleEvents(event);
    }
}
void Scene::update(float dt)
{
    Object::update(dt);
    for (auto it = children_screen_.begin(); it != children_screen_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_screen_.erase(it);
            child->clean();
            delete child;
            continue;
        }
        else if (child->getIsActive())
        {
            child->update(dt);
        }
        it++;
    }
    for (auto it = children_world_.begin(); it != children_world_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_world_.erase(it);
            child->clean();
            delete child;
            continue;
        }
        else if (child->getIsActive())
        {
            child->update(dt);
        }
        it++;
    }
}
void Scene::render()
{
    Object::render();
    for (auto child : children_world_)
    {
        if (child->getIsActive())
        {
            child->render();
        }
    }
    for (auto child : children_screen_)
    {
        if (child->getIsActive())
        {
            child->render();
        }
    }
}
void Scene::clean()
{
    Object::clean();
    for (auto child : children_world_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_world_.clear();
    for (auto child : children_screen_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_screen_.clear();
}
void Scene::addChild(Object *child)
{
    if (child != nullptr)
    {
        switch (child->getObjectType())
        {
        case ObjectType::SCREEN:
            children_screen_.push_back(dynamic_cast<ObjectScreen *>(child));
            break;
        case ObjectType::WORLD:
        SDL_Log("Add to World");
            children_world_.push_back(dynamic_cast<ObjectWorld *>(child));
            break;
        default:
            children_.push_back(child);
            break;
        }
    }
}
void Scene::removeChild(Object *child)
{
    if (child != nullptr)
    {
        switch (child->getObjectType())
        {
        case ObjectType::SCREEN:
            children_screen_.erase(std::remove(children_screen_.begin(), children_screen_.end(), child), children_screen_.end());
            break;
        case ObjectType::WORLD:
            children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), child), children_world_.end());
            break;
        default:
            children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
            break;
        }
    }
}
