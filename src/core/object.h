#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "def.h"
#include "game.h"

class Object
{
protected:
    Game &game_ = Game::getInstance();
    ObjectType object_type_ = ObjectType::NONE;
    std::vector<Object *> children_;
    bool is_active_ = true;
    bool need_remove_ = false;

public:
    Object() = default;
    virtual ~Object() = default; // 所有的类不在构造函数和析构函数中做任何事

    virtual void init();
    virtual void handleEvents(SDL_Event &);
    virtual void update(float);
    virtual void render();
    virtual void clean();

    virtual void addChild(Object *child);
    virtual void removeChild(Object *child);
    
    ObjectType getObjectType() { return object_type_; }
    bool isActive() { return is_active_; }
    void setActive(bool active) { is_active_ = active; }
    bool getNeedRemove() { return need_remove_; }
    void setNeedRemove(bool remove) { need_remove_ = remove; }
};