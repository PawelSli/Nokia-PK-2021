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

void BaseState::BTS_handleCallRequest(common::PhoneNumber phoneNumber)
{
    logger.logError("Uexpected: handleCallRequest: ",phoneNumber);
}

void BaseState::BTS_handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    logger.logError("Uexpected: handleUknownRecipient: ",recipientPhoneNumber);
}

void BaseState::USER_handleCallAccept()
{
    logger.logError("Uexpected: handleCallAccepted");
}

void BaseState::USER_handleCallDropReceiver()
{
    logger.logError("Uexpected: handleCallRejected");
}

void BaseState::BTS_handleCallAccept()
{
    logger.logError("Uexpected: BTS_handleCallAccept");
}

void BaseState::BTS_handleCallDrop()
{
    logger.logError("Uexpected: BTS_handleCallDrop");
}

void BaseState::USER_handleStartDial()
{
    logger.logError("Uexpected: USER_handleStartDial");
}

void BaseState::USER_handleCallRequest(common::PhoneNumber receiverPhoneNumber)
{
    logger.logError("Uexpected: USER_handleCallRequest: ",receiverPhoneNumber);
}

void BaseState::USER_handleCallDropSender(common::PhoneNumber receiverPhoneNumber)
{
    logger.logError("Uexpected: USER_handleCallDropSender: ",receiverPhoneNumber);
}

}
