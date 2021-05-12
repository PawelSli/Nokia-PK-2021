#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "../Models/Sms.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleReceivedSms(common::PhoneNumber senderPhoneNumber, std::string message)
{
    Sms incomingSms(senderPhoneNumber, message, false, false);
    context.smsDb.add(incomingSms);
    context.user.showReceivedSms();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

}
