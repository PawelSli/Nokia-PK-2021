#include "ConnectedState.hpp"
#include "TalkingState.hpp"
#include "NotConnectedState.hpp"
#include "Ports/UserPort.hpp"
#include <thread>


namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.USER_showConnected();
}

void ConnectedState::setSenderPhoneNumber(common::PhoneNumber senderPhoneNumber){
    this->senderPhoneNumber=senderPhoneNumber;
}

common::PhoneNumber ConnectedState::getSenderPhoneNumber(){
    return this->senderPhoneNumber;
}

void ConnectedState::BST_handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::BTS_handleCallRequest(common::PhoneNumber senderPhoneNumber)
{
    this->setSenderPhoneNumber(senderPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([this](){this->context.user.USER_showStartMenu();},30);
    context.user.USER_showCallRequest(senderPhoneNumber);

}

void ConnectedState::USER_handleCallAccept(common::PhoneNumber phoneNumber)
{
    context.timer.TIMER_stopTimer();
    std::cout<<"Accept call from:";
    context.bts.BTS_sendCallAccept(phoneNumber);
    context.user.USER_callAchieved(phoneNumber);
    context.setState<TalkingState>(phoneNumber);
}


void ConnectedState::BTS_handleCallAccept(common::PhoneNumber phoneNumber)
{
    context.timer.TIMER_stopTimer();
    context.user.USER_callAchieved(phoneNumber);
    context.setState<TalkingState>(phoneNumber);
}

void ConnectedState::BTS_handleCallDrop(common::PhoneNumber phoneNumber)
{
    context.timer.TIMER_stopTimer();
    std::printf("Accept call from:");
    context.user.USER_showPartnerNotAvailable(phoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([this](){this->context.user.USER_showStartMenu();},2);
}

void ConnectedState::BTS_handleUknownRecipient(common::PhoneNumber receiverPhoneNumber)
{
    context.timer.TIMER_stopTimer();
    context.user.USER_showPartnerNotAvailable(receiverPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([this](){this->context.user.USER_showStartMenu();},2);
}

void ConnectedState::USER_handleStartDial()
{
    context.user.USER_showEnterPhoneNumber();
}

void ConnectedState::USER_handleCallRequest(common::PhoneNumber receiverPhoneNumber)
{
    context.bts.BTS_sendCallRequest(receiverPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([this](){this->context.user.USER_showStartMenu();},60);
    context.user.USER_showDialing(receiverPhoneNumber);
}

void ConnectedState::USER_handleCallDrop(common::PhoneNumber receiverPhoneNumber)
{
    context.timer.TIMER_stopTimer();
    context.bts.BTS_sendCallDrop(receiverPhoneNumber);
    context.user.USER_showStartMenu();
}

}
