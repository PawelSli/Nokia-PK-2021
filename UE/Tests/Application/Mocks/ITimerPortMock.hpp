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

    MOCK_METHOD(void, TIMER_startTimer, (double duration,int i), (final));
    MOCK_METHOD(void, TIMER_startTimerAndDoSomething, (std::function<void()>,double duration,int i), (final));
    MOCK_METHOD(void, TIMER_stopTimer, (int i), (final));
};

}


