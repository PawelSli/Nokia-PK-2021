#include "ConnectedState.hpp"
#include "TalkingState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::setSenderPhoneNumber(common::PhoneNumber senderPhoneNumber){
    this->senderPhoneNumber=senderPhoneNumber;
}

common::PhoneNumber ConnectedState::getSenderPhoneNumber(){
    return this->senderPhoneNumber;
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}
//TODO:
void ConnectedState::handleCallRequest(common::PhoneNumber senderPhoneNumber)
{
    this->setSenderPhoneNumber(senderPhoneNumber);
    context.user.showCallRequest(senderPhoneNumber);
    using namespace std::chrono_literals;
    context.timer.startTimer(30s);

}
//TODO:
void ConnectedState::handleCallAccepted()
{
    context.timer.stopTimer();
    context.bts.sendCallAccept(getSenderPhoneNumber());
    context.setState<TalkingState>(senderPhoneNumber);
}

void ConnectedState::handleCallRejected()
{
    context.timer.stopTimer();
    context.bts.sendCallDrop(this->getSenderPhoneNumber());
    context.user.showStartMenu();

}

}
