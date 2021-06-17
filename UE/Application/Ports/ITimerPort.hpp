#pragma once

#include <chrono>
#include <functional>

namespace ue
{

class ITimerEventsHandler
{
public:
    virtual ~ITimerEventsHandler() = default;

    virtual void TIMER_handleTimeout() = 0;
};

class ITimerPort
{
public:
    using Duration = std::chrono::milliseconds;

    virtual ~ITimerPort() = default;

    virtual void TIMER_startTimer(double,int) = 0;
    virtual void TIMER_stopTimer(int) = 0;
    virtual void TIMER_startTimerAndDoSomething(std::function<void()>,double duration,int) = 0;
    virtual bool TIMER_checkTimer(int) =0;

};

}
