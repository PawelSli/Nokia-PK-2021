#include "TalkingState.hpp"
#include "ConnectedState.hpp"
#include <thread>

namespace ue {


TalkingState::TalkingState(Context &context,common::PhoneNumber phoneNumber)
    : BaseState(context, "TalkingState"), caller{phoneNumber}
{
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        this->context.timer.TIMER_stopTimer(3);
        this->context.setState<ConnectedState>();
    },180,3);
    context.user.USER_startTalking(phoneNumber);
}

void TalkingState::BTS_handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    context.timer.TIMER_stopTimer(3);
    context.user.USER_showPartnerNotAvailable(recipientPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        this->context.timer.TIMER_stopTimer(3);
        this->context.setState<ConnectedState>();
    },2,3);

}

void TalkingState::handleSendTalkMessage(const std::string msg)
{
    context.timer.TIMER_stopTimer();
    context.timer.TIMER_startTimerAndDoSomething([&](){this->context.user.showCallView(msg);},120);
    context.bts.sendTalkMessage(msg,caller );
}

void TalkingState::handleTalkMessage(const std::string msg)
{
    context.timer.TIMER_stopTimer();
    context.timer.TIMER_startTimerAndDoSomething([&](){this->context.user.showCallView(msg);},120);
    context.user.showCallView(msg);
}
}

