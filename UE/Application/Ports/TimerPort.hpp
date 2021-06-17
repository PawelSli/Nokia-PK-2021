#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include <chrono>
#include<map>
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
    void TIMER_startTimer(double duration,int i) override;
    void TIMER_startTimerAndDoSomething(std::function<void()>,double duration,int i) override;
    void TIMER_stopTimer(int i) override;
    bool TIMER_checkTimer(int i) override;

private:
    std::map<int,bool> timers;
    common::PrefixedLogger logger;
    ITimerEventsHandler* handler = nullptr;
    std::chrono::steady_clock::time_point beggining;
    std::chrono::steady_clock::time_point ending;
};

}
