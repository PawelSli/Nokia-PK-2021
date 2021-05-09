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

void ConnectedState::handleSmsReceived(int number, std::string text)
{
    Sms incomingSms(number, text);
    incomingSms.read = false;
    incomingSms.sent = false;
    context.db.insert(incomingSms);
    context.user.showReceivedSms();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

}
