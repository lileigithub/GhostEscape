#include "object.h"

void Object::handleEvents(SDL_Event &event)
{
    for (auto &child : children_)
    {
        if (child->getIsActive())
        {
            child->handleEvents(event);
        }
    }
}

void Object::update(float dt)
{
    for (auto &child : need_add_children_)
    {
        children_.push_back(child);
    }
    need_add_children_.clear();
    
    for (auto it = children_.begin(); it != children_.end();)
    {
        auto child = *it;
        if (child->need_remove_)
        {
            it = children_.erase(it);
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

void Object::render()
{
    for (auto &child : children_)
    {
        if (child->getIsActive())
        {
            child->render();
        }
    }
}

void Object::clean()
{
    for (auto &child : children_)
    {
        child->clean();
        delete child;
        child = nullptr;
    }
    children_.clear();
}

void Object::addChild(Object *child)
{
    if (child != nullptr)
    {
        need_add_children_.push_back(child); 
    }
}

void Object::removeChild(Object *child)
{
    if (child != nullptr)
    {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }
}
