#include "object.h"

void Object::init()
{
}

void Object::handleEvents(SDL_Event &event)
{
    for (auto it = children_.begin(); it != children_.end();)
    {
        auto child = *it;
        if (child->need_remove_)
        {
            it = children_.erase(it);
            child->clean();
            delete child;
            continue;
        }
        else if (child->isActive())
        {
            child->handleEvents(event);
        }
        it++;
    }
}

void Object::update(float dt)
{
    for (auto &child : children_)
    {
        if (child->isActive())
        {
            child->update(dt);
        }
    }
}

void Object::render()
{
    for (auto &child : children_)
    {
        if (child->isActive())
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
    }
    children_.clear();
}

void Object::addChild(Object *child)
{
    if (child != nullptr)
    {
        children_.push_back(child);
    }
}

void Object::removeChild(Object *child)
{
    if (child != nullptr)
    {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }
}
