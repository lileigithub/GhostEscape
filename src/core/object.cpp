#include "object.h"

void Object::init()
{
}

void Object::handleEvents(SDL_Event &event)
{
    for (auto &child : children_)
    {
        child->handleEvents(event);
    }
}

void Object::update(float dt)
{
    for (auto &child : children_)
    {
        child->update(dt);
    }
}

void Object::render()
{
    for (auto &child : children_)
    {
        child->render();
    }
}

void Object::clean()
{
    for (auto &child : children_)
    {
        child->clean();
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
