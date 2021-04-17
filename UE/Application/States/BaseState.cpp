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

void BaseState::handleTimeout()
{
    logger.logError("Uexpected: handleTimeout");
}

void BaseState::handleDisconnected()
{
    logger.logError("Uexpected: handleDisconnected");
}

void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Uexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept()
{
    logger.logError("Uexpected: handleAttachAccept");
}

void BaseState::handleAttachReject()
{
    logger.logError("Uexpected: handleAttachReject");
}

//TODO: CONNECTED-STATE
void BaseState::handleCallRequest()
{
    logger.logError("Uexpected: handleCallRequest");
}

//TODO: TALKING-STATE
void BaseState::handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    logger.logError("Uexpected: handleUknownRecipient: ",recipientPhoneNumber);
}

//TODO: CONNECTED-STATE
void BaseState::handleCallAccepted()
{
    logger.logError("Uexpected: handleCallAccepted");
}

//TODO: CONNECTED-STATE
void BaseState::handleCallRejected()
{
    logger.logError("Uexpected: handleCallRejected");
}

}
