#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer)
    : context{iLogger, bts, user, timer},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::TIMER_handleTimeout()
{
    context.state->TIMER_handleTimeout();
}

void Application::BST_handleDisconnected()
{
    context.state->BST_handleDisconnected();
}

void Application::BTS_handleSib(common::BtsId btsId)
{
    context.state->BTS_handleSib(btsId);
}

void Application::BTS_handleAttachAccept()
{
    context.state->BTS_handleAttachAccept();
}

void Application::BTS_handleAttachReject()
{
    context.state->BTS_handleAttachReject();
}

void Application::BTS_handleCallRequest(common::PhoneNumber phoneNumber)
{
    context.state->BTS_handleCallRequest(phoneNumber);
}

void Application::USER_handleCallAccept()
{
    context.state->USER_handleCallAccept();
}

void Application::USER_handleCallDropReceiver()
{
    context.state->USER_handleCallDropReceiver();
}

void Application::BTS_handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    context.state->BTS_handleUknownRecipient(recipientPhoneNumber);
}

void Application::BTS_handleCallAccept()
{
    context.state->BTS_handleCallAccept();
}

void Application::BTS_handleCallDrop()
{
    context.state->BTS_handleCallDrop();
}

void Application::USER_handleStartDial()
{
    context.state->USER_handleStartDial();
}

void Application::USER_handleCallRequest(common::PhoneNumber receiverPhoneNumber)
{
    context.state->USER_handleCallRequest(receiverPhoneNumber);
}

void Application::USER_handleCallDropSender(common::PhoneNumber receiverPhoneNumber)
{
    context.state->USER_handleCallDropSender(receiverPhoneNumber);
}

}
