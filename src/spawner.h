#pragma once
#include "core/object.h"

class Player;
class Spawner : public Object {
    protected:
    int num_ = 5;
    float timer_ = 0.0f;
    float interval_ = 3.0f;
    Player* player_;

    public:

    void update(float dt) override;

    void setNum(int num) { num_ = num; }
    int getNum() { return num_; }
    void setTimer(float timer) { timer_ = timer; }
    float getTimer() { return timer_; }
    void setInterval(float interval) { interval_ = interval; }
    float getInterval() { return interval_; }
    void setPlayer(Player* player) { player_ = player; }
    Player* getPlayer() { return player_; }
};