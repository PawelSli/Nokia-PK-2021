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
    void TIMER_handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSmsToUnknownRecipient() override;
    void BST_handleDisconnected() override;
    void BTS_handleSib(common::BtsId btsId) override;
    void BTS_handleAttachAccept() override;
    void BTS_handleAttachReject() override;
    void BTS_handleCallRequest(common::PhoneNumber phoneNumber) override;
    void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber) override;
    void BTS_handleCallAccept(common::PhoneNumber receiverPhoneNumber) override;
    void BTS_handleCallDrop(common::PhoneNumber receiverPhoneNumber) override;

    //IUserEventsHandler interface:
    void USER_handleCallAccept(common::PhoneNumber) override;
    void USER_handleStartDial() override;
    void USER_handleCallRequest(common::PhoneNumber) override;
    void USER_handleCallDrop(common::PhoneNumber) override;
    void handleSendTalkMessage(const std::string txt) override;
    void handleTalkMessage(const std::string) override;
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


