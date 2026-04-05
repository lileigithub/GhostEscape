#include "timer.h"

Timer *Timer::createTimerAddChild(Object *parent, float interval)
{
    Timer *timer = new Timer();
    timer->interval_ = interval;
    timer->is_active_ = false;
    if (parent) {
        parent->addChild(timer);
    }
    return timer;
}

void Timer::update(float dt)
{
    timer_+= dt;
    if (timer_ >= interval_) {
        timer_ = 0.0f;
        is_time_out_ = true;
    }
}

bool Timer::getResetIsTimeOut()
{
    if (is_time_out_) {
        is_time_out_ = false;
        return true;
    }
    return false;
}
