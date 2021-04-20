#include "TimerPort.hpp"

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

void TimerPort::startTimer(Duration duration)
{
    logger.logDebug("Start timer: ", duration.count(), "ms");
}

void TimerPort::stopTimer()
{
    logger.logDebug("Stop timer");
}

}
