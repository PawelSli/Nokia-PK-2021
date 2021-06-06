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


void ConnectedState::handleShowMessage(int index)
{
    Sms* message = context.smsDb.getMessage(index);
    message->read = true;

    std::vector<Sms> messages = context.smsDb.getAllMessages();
    bool areAllMessagesRead = true;
    for(Sms message : messages)
    {
        if(!message.read)
        {
            areAllMessagesRead = false;
        }
    }

    context.user.showMessage(*message, areAllMessagesRead);
}

void ConnectedState::handleSmsToUnknownRecipient()
{
    Sms* message = context.smsDb.getLastMessage();
    if(message != NULL){
        message->failed = true;
    }
}

}
