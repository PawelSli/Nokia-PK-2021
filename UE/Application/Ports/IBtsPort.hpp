#pragma once

#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void BST_handleDisconnected() = 0;
    virtual void BTS_handleSib(common::BtsId) = 0;
    virtual void BTS_handleAttachAccept() = 0;
    virtual void BTS_handleAttachReject() = 0;
    virtual void BTS_handleCallRequest(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleCallAccept()=0;
    virtual void BTS_handleCallDrop()=0;

};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void BTS_sendAttachRequest(common::BtsId) = 0;
    virtual void BTS_sendCallAccept(common::PhoneNumber)=0;
    virtual void BTS_sendCallDropFromReceiver(common::PhoneNumber)=0;
    virtual void BTS_sendCallRequest(common::PhoneNumber)=0;
    virtual void BTS_sendCallDropFromCaller(common::PhoneNumber)=0;

};

}
