#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleSmsToUnknownRecipient() override;

<<<<<<< HEAD
    // IUserEventsHandler
=======
    // IUserEventsHandler interface
>>>>>>> 389db2ff21770a3cf47ddc6c816eeae2026030fc
    void handleReceivedMessage(Sms& sms) override;
    void handleShowAllMessages() override;
    void handleSendMessage(Sms& sms) override;
    void handleSmsCreate() override;
    void handleShowMessage(int index) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
