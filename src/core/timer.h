#pragma once
#include "object.h"
class Timer : public Object
{
    float timer_ = 0.0f;
    float interval_ = 0.0f;
    bool is_time_out_ = false;
    float progress_ = 0.0f;

public:
    static Timer *createTimerAddChild(Object *parent, float interval);

    void update(float dt) override;

    void start()
    {
        timer_ = 0.0f;
        is_time_out_ = false;
        is_active_ = true;
    }
    bool isStart() { return is_active_; }
    void stop() { is_active_ = false; }
    bool getResetIsTimeOut();
    float getProgress() const { return timer_ / interval_; }
};