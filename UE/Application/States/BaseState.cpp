#include "BaseState.hpp"

namespace ue
{

BaseState::BaseState(Context &context, const std::string &name)
    : context(context),
      logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::TIMER_handleTimeout()
{
    logger.logError("Uexpected: handleTimeout");
}


void BaseState::BST_handleDisconnected()
{
    logger.logError("Uexpected: handleDisconnected");
}


void BaseState::BTS_handleSib(common::BtsId btsId)
{
    logger.logError("Uexpected: handleSib: ", btsId);
}

void BaseState::BTS_handleAttachAccept()
{
    logger.logError("Uexpected: handleAttachAccept");
}

void BaseState::BTS_handleAttachReject()
{
    logger.logError("Uexpected: handleAttachReject");
}

void BaseState::handleReceivedMessage(Sms& sms)
{
   logger.logError("Unexpected: handleReceivedMessage");
}

void BaseState::handleSendMessage(Sms& sms)
{
    logger.logError("Unexpected: handleSendMessage");
}

void BaseState::handleShowAllMessages()
{
    logger.logError("Unexpected: handleShowAllMessages");
}

void BaseState::handleSmsCreate()
{
    logger.logError("Unexpected: handleSmsCreate");
}


void BaseState::handleShowMessage(int index)
{
    logger.logError("Unexpected: handleShowMessage");
}

void BaseState::handleSmsToUnknownRecipient()
{
    logger.logError("Unexpected: handleSmsToUnknownRecipient");
}
  
void BaseState::BTS_handleCallRequest(common::PhoneNumber phoneNumber)
{
    logger.logError("Uexpected: handleCallRequest: ",phoneNumber);
}

void BaseState::BTS_handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    logger.logError("Uexpected: handleUknownRecipient: ",recipientPhoneNumber);
}

void BaseState::USER_handleCallAccept(common::PhoneNumber receiverPhoneNumber)
{
    logger.logError("Uexpected: handleCallAccepted: ",receiverPhoneNumber);
}

void BaseState::BTS_handleCallAccept(common::PhoneNumber receiverPhoneNumber)
{
    logger.logError("Uexpected: BTS_handleCallAccept: ",receiverPhoneNumber);
}

void BaseState::BTS_handleCallDrop(common::PhoneNumber receiverPhoneNumber)
{
    logger.logError("Uexpected: BTS_handleCallDrop: ",receiverPhoneNumber);
}

void BaseState::USER_handleStartDial()
{
    logger.logError("Uexpected: USER_handleStartDial");
}

void BaseState::USER_handleCallRequest(common::PhoneNumber receiverPhoneNumber)
{
    logger.logError("Uexpected: USER_handleCallRequest: ",receiverPhoneNumber);
}

void BaseState::USER_handleCallDrop(common::PhoneNumber receiverPhoneNumber)
{
    logger.logError("Uexpected: USER_handleCallDropSender: ",receiverPhoneNumber);
}
void BaseState::handleSendTalkMessage(const std::string msg)
{
    logger.logError("Unexpected h send talk msg",msg);
}
void BaseState::handleTalkMessage(const std::string msg)
{
    logger.logError("Unexpected handl;e talk ",msg);
}

}
