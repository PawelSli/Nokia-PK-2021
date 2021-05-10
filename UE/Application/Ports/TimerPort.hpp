#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include <chrono>
#include <thread>

namespace ue
{

class TimerPort : public ITimerPort
{
public:
    TimerPort(common::ILogger& logger);

    void start(ITimerEventsHandler& handler);
    void stop();

    // ITimerPort interface
    void TIMER_startTimer(double duration) override;
    void TIMER_startTimerAndDoSomething(std::function<void()>,double duration) override;
    void TIMER_stopTimer() override;

private:
    bool active = false;
    common::PrefixedLogger logger;
    ITimerEventsHandler* handler = nullptr;
    std::chrono::steady_clock::time_point beggining;
    std::chrono::steady_clock::time_point ending;
};

}
