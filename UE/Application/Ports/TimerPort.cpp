#include "TimerPort.hpp"
#include <atomic>

namespace ue
{

TimerPort::TimerPort(common::ILogger &logger)
    : logger(logger, "[TIMER PORT]")
{}


void TimerPort::start(ITimerEventsHandler &handler)
{
    logger.logDebug("Started");
    beggining=std::chrono::steady_clock::now();
    this->handler = &handler;
}

void TimerPort::stop()
{
    ending=std::chrono::steady_clock::now();
    auto timePass=std::chrono::duration_cast<std::chrono::microseconds>(ending-beggining).count();
    logger.logDebug("Stoped after number of miniseconds: ",timePass);
    handler = nullptr;

}

void TimerPort::TIMER_startTimer(double duration, int i)
{
    logger.logDebug("Start timer: ", duration*1000, "ms");
    timers[i]=false;
    std::thread t([=]() {
        if(timers[i]) return;
        int temp = (int)(duration*1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(temp));
        if(timers[i]) return;
    });
    t.detach();
}

void TimerPort::TIMER_startTimerAndDoSomething(std::function<void()> function,double duration,int i)
{
    logger.logDebug("Start timer: ", duration*1000, "ms");
    timers[i]=false;
    std::thread t([=]() {
        if(timers[i]) return;
        int temp = (int)(duration*1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(temp));
        if(timers[i]) return;
        function();
    });
    t.detach();
}

void TimerPort::TIMER_stopTimer(int i)
{
    logger.logDebug("Stop timer");
    timers[i]=true;
}

}
