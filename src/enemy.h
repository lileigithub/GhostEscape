#pragma once

#include "core/actor.h"

class Player;

class Enemy : public Actor
{
protected:
    ObjectWord *target_ = nullptr;

public:
    Enemy(ObjectWord *target)
    {
        target_ = target;
    }

    void init() override;

    void update(float dt) override;

    void aimTarget();
};