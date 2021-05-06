#include "ConnectingState.hpp"
#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectingState::ConnectingState(Context &context, common::BtsId btsId)
    : BaseState(context, "ConnectingState")
{
    context.user.USER_showConnecting();
    context.bts.BTS_sendAttachRequest(btsId);
    using namespace std::chrono_literals;
    context.timer.TIMER_startTimer(500ms);
}

void ConnectingState::TIMER_handleTimeout()
{
    context.setState<NotConnectedState>();
}

void ConnectingState::BTS_handleAttachAccept()
{
    context.timer.TIMER_stopTimer();
    context.setState<ConnectedState>();
}

void ConnectingState::BTS_handleAttachReject()
{
    context.timer.TIMER_stopTimer();
    context.setState<NotConnectedState>();
}

}


