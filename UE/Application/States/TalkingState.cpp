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
    },120,3);
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
    context.timer.TIMER_stopTimer(3);
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        this->context.timer.TIMER_stopTimer(3);
        this->context.setState<ConnectedState>();// context.user.showCallView(msg);
    },120,3);
    context.bts.sendTalkMessage(msg,caller );
}

void TalkingState::handleTalkMessage(const std::string msg)
{
    context.timer.TIMER_stopTimer(3);
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        this->context.timer.TIMER_stopTimer(3);
        this->context.setState<ConnectedState>();// context.user.showCallView(msg);
    },120,3);
    context.user.showCallView(msg);
}

void TalkingState::BTS_handleCallDrop(common::PhoneNumber receiver)
{
    context.timer.TIMER_stopTimer(3);
    context.user.showcallDropping(receiver);
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        this->context.timer.TIMER_stopTimer(3);
        this->context.setState<ConnectedState>();
    },2,3);

}

void TalkingState::handleReceivedMessage(Sms& incomingSms)
{
    context.smsDb.addMessage(incomingSms);
    context.user.showSmsReceivedNotification();
}

void TalkingState::USER_handleCallDrop(common::PhoneNumber callingPhoneNumber)
{
    context.bts.BTS_sendCallDrop(caller);
    context.timer.TIMER_stopTimer(3);
    context.user.showcallDropping(context.bts.getPhoneNumber());
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        this->context.timer.TIMER_stopTimer(3);
        this->context.setState<ConnectedState>();
    },2,3);

}
}

