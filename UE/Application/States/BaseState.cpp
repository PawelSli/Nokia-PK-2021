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

}
