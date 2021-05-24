#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "Sms.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleReceivedMessage(Sms& incomingSms)
{
    context.smsDb.addMessage(incomingSms);
    context.user.showSmsReceivedNotification();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleSendMessage(Sms& sms)
{
    context.smsDb.addMessage(sms);
    context.bts.sendMessage(sms);
}

void ConnectedState::handleShowAllMessages()
{
    std::vector<Sms> messages = context.smsDb.getAllMessages();
    context.user.showAllMessages(messages);
}

void ConnectedState::handleSmsCreate()
{
    context.user.showSmsToCreate();
}

}
