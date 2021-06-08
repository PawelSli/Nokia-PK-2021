#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer);
    ~Application();

    // ITimerEventsHandler interface
    void TIMER_handleTimeout() override;

    // IBtsEventsHandler interface
    void BST_handleDisconnected() override;
    void BTS_handleSib(common::BtsId btsId) override;
    void BTS_handleAttachAccept() override;
    void BTS_handleAttachReject() override;
    void BTS_handleCallRequest(common::PhoneNumber phoneNumber) override;
    void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber) override;
    void BTS_handleCallAccept(common::PhoneNumber phoneNumber) override;
    void BTS_handleCallDrop(common::PhoneNumber phoneNumber) override;

    //IUserEventsHandler interface:
    void USER_handleCallAccept(common::PhoneNumber phoneNumber) override;
    void USER_handleStartDial() override;
    void USER_handleCallRequest(common::PhoneNumber) override;
    void USER_handleCallDrop(common::PhoneNumber) override;
    void handleSendTalkMessage(const std::string txt) override;
    void handleTalkMessage(const std::string) override;

private:
    Context context;
    common::PrefixedLogger logger;

};

}
