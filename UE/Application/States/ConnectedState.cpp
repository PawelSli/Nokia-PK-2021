#include "ConnectedState.hpp"
#include "Sms.hpp"
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

void ConnectedState::handleReceivedMessage(Sms& incomingSms)
{
    context.smsDb.addMessage(incomingSms);
    context.user.showSmsReceivedNotification();
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
    message->failed = true;
}
  
void ConnectedState::BTS_handleCallRequest(common::PhoneNumber senderPhoneNumber)
{
    setSenderPhoneNumber(senderPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        context.timer.TIMER_stopTimer(2);
        context.setState<ConnectedState>();
    },60,2);
    context.user.USER_showCallRequest(senderPhoneNumber);

}

void ConnectedState::USER_handleCallAccept(common::PhoneNumber phoneNumber)
{
    context.timer.TIMER_stopTimer(2);
    context.bts.BTS_sendCallAccept(phoneNumber);
    context.user.USER_callAchieved(phoneNumber);
    context.setState<TalkingState>(phoneNumber);
}


void ConnectedState::BTS_handleCallAccept(common::PhoneNumber phoneNumber)
{
    if(context.timer.TIMER_checkTimer(2)){
        context.timer.TIMER_stopTimer(2);
        context.user.USER_callAchieved(phoneNumber);
        context.setState<TalkingState>(phoneNumber);
    }
}

void ConnectedState::BTS_handleCallDrop(common::PhoneNumber phoneNumber)
{
    if(context.timer.TIMER_checkTimer(2)){
        context.user.USER_showPartnerNotAvailable(phoneNumber);
        context.timer.TIMER_startTimerAndDoSomething([&]()
        {
            context.timer.TIMER_stopTimer(2);
            context.setState<ConnectedState>();

        },2,2);
    }
}

void ConnectedState::BTS_handleUknownRecipient(common::PhoneNumber receiverPhoneNumber)
{
    context.timer.TIMER_stopTimer(2);
    context.user.USER_showPartnerDoesNotExist(senderPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        context.timer.TIMER_stopTimer(2);
        context.setState<ConnectedState>();
    },2,2);
}

void ConnectedState::USER_handleStartDial()
{
    context.user.USER_showEnterPhoneNumber();
}

void ConnectedState::USER_handleCallRequest(common::PhoneNumber receiverPhoneNumber)
{
    setSenderPhoneNumber(receiverPhoneNumber);
    context.bts.BTS_sendCallRequest(receiverPhoneNumber);
    context.timer.TIMER_startTimerAndDoSomething([&]()
    {
        context.timer.TIMER_stopTimer(2);
        context.setState<ConnectedState>();
    },60,2);
    context.user.USER_showDialing(receiverPhoneNumber);
}

void ConnectedState::USER_handleCallDrop()
{
    context.timer.TIMER_stopTimer(2);
    context.bts.BTS_sendCallDrop(senderPhoneNumber);
    context.setState<ConnectedState>();
}

}
