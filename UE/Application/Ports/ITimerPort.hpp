#pragma once

#include <chrono>

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

    virtual void TIMER_startTimer(Duration) = 0;
    virtual void TIMER_stopTimer() = 0;

};

}
