#include "spawner.h"
#include "core/scene.h"
#include "enemy.h"
#include "player.h"
#include "world/effect.h"

void Spawner::update(float dt)
{
    if (player_ == nullptr || !player_->getIsActive())
    {
        return;
    }
    Object::update(dt);
    timer_ += dt;
    if (timer_ >= interval_)
    {
        timer_ = 0;
        for (int i = 0; i < num_; i++)
        {
            auto pos = game_.randomVec2(game_.getCurrentScene()->getCameraPos(), game_.getCurrentScene()->getCameraPos() + game_.getSceneSize());
            Enemy *enemy = new Enemy(player_);
            enemy->init();
            enemy->setPosition(pos);
            Effect::createEffectAddChild(game_.getCurrentScene(), "assets/effect/184_3_.png", enemy->getPosition(), 1.0f, enemy);
        }
    }
}