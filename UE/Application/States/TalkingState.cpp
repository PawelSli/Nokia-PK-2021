#include "TalkingState.hpp"
#include "ConnectedState.hpp"
#include <thread>

namespace ue {


TalkingState::TalkingState(Context &context,common::PhoneNumber phoneNumber)
    : BaseState(context, "TalkingState"), caller{phoneNumber}
{
    context.user.USER_startTalking(phoneNumber);
    std::cout<<"HMMMMMM"<<std::endl;
}

void TalkingState::BTS_handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    context.timer.TIMER_stopTimer();
    context.user.USER_showPartnerNotAvailable(recipientPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([this](){this->context.setState<ConnectedState>();},2);

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

