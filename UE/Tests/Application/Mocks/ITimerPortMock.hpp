#pragma once

#include <gmock/gmock.h>
#include "Ports/ITimerPort.hpp"

namespace ue
{

class ITimerEventsHandlerMock : public ITimerEventsHandler
{
public:
    ITimerEventsHandlerMock();
    ~ITimerEventsHandlerMock() override;

    MOCK_METHOD(void, TIMER_handleTimeout, (), (final));

};

class ITimerPortMock : public ITimerPort
{
public:
    ITimerPortMock();
    ~ITimerPortMock() override;

    MOCK_METHOD(void, TIMER_startTimer, (double duration), (final));
    MOCK_METHOD(void, TIMER_startTimerAndDoSomething, (std::function<void()>,double duration), (final));
    MOCK_METHOD(void, TIMER_stopTimer, (), (final));
};

}

/*
class ITimerEventsHandler
{
public:
    virtual ~ITimerEventsHandler() = default;

    virtual void TIMER_handleTimeout() = 0;
};
 virtual void TIMER_startTimerAndDoSomething(std::function<void()>,double duration) = 0;
class ITimerPort
{
public:
    using Duration = std::chrono::milliseconds;

    virtual ~ITimerPort() = default;

    virtual void TIMER_startTimer(Duration) = 0;
    virtual void TIMER_stopTimer() = 0;

};

}

*/
