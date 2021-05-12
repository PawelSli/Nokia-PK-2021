#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

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
    void handleCallRequest(common::PhoneNumber phoneNumber) override;
    void handleUknownRecipient(common::PhoneNumber phoneNumber) override;

    //IUserEventsHandler interface:
    void handleCallAccepted() override;
    void handleCallRejected() override;



protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
