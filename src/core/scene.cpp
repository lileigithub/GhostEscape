#include "scene.h"
#include "../screen/ui_mouse.h"

glm::vec2 Scene::wordPosToScreenPos(glm::vec2 wordPos)
{
    return wordPos - cameraPos_;
}

glm::vec2 Scene::screenPosToWorldPos(glm::vec2 screenPos)
{
    return screenPos + cameraPos_;
}

glm::vec2 Scene::getMousePos()
{
    return ui_mouse_->getScreenPos() + cameraPos_;
}

glm::vec2 Scene::getMouseScreenPos()
{
    return ui_mouse_->getScreenPos();
}

void Scene::setCameraPos(glm::vec2 cameraPos)
{
    cameraPos_ = glm::clamp(cameraPos, glm::vec2(-30.0f, -30.0f), wordSize_ - game_.getSceneSize() + 30.0f);
}

void Scene::setIsPause(bool is_pause)
{
    is_pause_ = is_pause;
    if (is_pause_)
        game_.pauseChunk();
    else
        game_.resumeChunk();
}

bool Scene::handleEvents(SDL_Event &event)
{
    for (auto child : children_screen_)
    {
        if (child->handleEvents(event))
            return true;
    }

    if (is_pause_)
        return true;
    for (auto child : children_world_)
    {
        if (child->handleEvents(event))
            return true;
    }
    if (Object::handleEvents(event))
        return true;
    return false;
}
void Scene::update(float dt)
{

    // 安全add
    for (auto &child : sceen_need_add_children_)
    {
        switch (child->getObjectType())
        {
        case ObjectType::SCREEN:
            children_screen_.push_back(dynamic_cast<ObjectScreen *>(child));
            break;
        case ObjectType::WORLD:
        case ObjectType::ENEMY:
            children_world_.push_back(dynamic_cast<ObjectWorld *>(child));
            break;
        default:
            children_.push_back(child);
            break;
        }
    }
    sceen_need_add_children_.clear();

    // 安全移除
    if (!is_pause_)
    {
        Object::update(dt);
        for (auto it = children_world_.begin(); it != children_world_.end();)
        {
            auto child = *it;
            if (child->getNeedRemove())
            {
                it = children_world_.erase(it);
                child->clean();
                delete child;
                child = nullptr;
                continue;
            }
            else if (child->getIsActive())
            {
                child->update(dt);
            }
            it++;
        }
    }

    for (auto it = children_screen_.begin(); it != children_screen_.end();)
    {
        auto child = *it;
        if (child->getNeedRemove())
        {
            it = children_screen_.erase(it);
            child->clean();
            delete child;
            child = nullptr;
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
        sceen_need_add_children_.push_back(child);
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
        case ObjectType::ENEMY:
            children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), child), children_world_.end());
            break;
        default:
            children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
            break;
        }
    }
}
