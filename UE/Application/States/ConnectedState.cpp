#include "ConnectedState.hpp"
#include "TalkingState.hpp"
#include "NotConnectedState.hpp"
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
    context.user.USER_showCallRequest(senderPhoneNumber);
    using namespace std::chrono_literals;
    context.timer.TIMER_startTimer(30s);

}

void ConnectedState::USER_handleCallAccept()
{
    context.timer.TIMER_stopTimer();
    context.bts.BTS_sendCallAccept(getSenderPhoneNumber());
    context.setState<TalkingState>(senderPhoneNumber);
}

void ConnectedState::USER_handleCallDropReceiver()
{
    context.timer.TIMER_stopTimer();
    context.bts.BTS_sendCallDropFromReceiver(this->getSenderPhoneNumber());
    context.user.USER_showStartMenu();

}

void ConnectedState::BTS_handleCallAccept()
{
    context.timer.TIMER_stopTimer();
    context.setState<TalkingState>(senderPhoneNumber);
}

void ConnectedState::BTS_handleCallDrop()
{
    context.timer.TIMER_stopTimer();
    context.user.USER_showStartMenu();
}

void ConnectedState::BTS_handleUknownRecipient(common::PhoneNumber receiverPhoneNumber)
{
    context.timer.TIMER_stopTimer();
    context.user.USER_showPartnerNotAvailable(receiverPhoneNumber);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
    context.user.USER_showStartMenu();
}

void ConnectedState::USER_handleStartDial()
{
    context.user.USER_showEnterPhoneNumber();
}

void ConnectedState::USER_handleCallRequest(common::PhoneNumber receiverPhoneNumber)
{
    context.bts.BTS_sendCallRequest(receiverPhoneNumber);
    using namespace std::chrono_literals;
    context.timer.TIMER_startTimer(60*1000ms);
    context.user.USER_showDialing(receiverPhoneNumber);
}

void ConnectedState::USER_handleCallDropSender(common::PhoneNumber receiverPhoneNumber)
{
    context.timer.TIMER_stopTimer();
    context.bts.BTS_sendCallDropFromCaller(receiverPhoneNumber);
    context.user.USER_showStartMenu();
}

}
