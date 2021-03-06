#pragma once

#include "Messages/BtsId.hpp"
#include "../Sms.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleReceivedMessage(Sms& sms) = 0;
    virtual void handleSmsToUnknownRecipient() = 0;
    virtual void BST_handleDisconnected() = 0;
    virtual void BTS_handleSib(common::BtsId) = 0;
    virtual void BTS_handleAttachAccept() = 0;
    virtual void BTS_handleAttachReject() = 0;
    virtual void BTS_handleCallRequest(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleCallAccept(common::PhoneNumber receiverPhoneNumber)=0;
    virtual void BTS_handleCallDrop(common::PhoneNumber receiverPhoneNumber)=0;
    virtual void handleTalkMessage(const std::string)=0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendMessage(Sms& sms) = 0;
    virtual void BTS_sendAttachRequest(common::BtsId) = 0;
    virtual void BTS_sendCallAccept(common::PhoneNumber)=0;
    virtual void BTS_sendCallDrop(common::PhoneNumber)=0;
    virtual void BTS_sendCallRequest(common::PhoneNumber)=0;
    virtual void sendTalkMessage(const std::string, common::PhoneNumber)=0;
    virtual common::PhoneNumber getPhoneNumber()=0;
};

}
