#pragma once

#include "BaseState.hpp"
#include <functional>

namespace ue
{

class ConnectedState : public BaseState
{
private:
    common::PhoneNumber senderPhoneNumber;
public:
    ConnectedState(Context& context);
    void setSenderPhoneNumber(common::PhoneNumber senderPhoneNumber);
    common::PhoneNumber getSenderPhoneNumber();

    // IBtsEventsHandler interface
public:
    void BST_handleDisconnected() final;
    void BTS_handleCallRequest(common::PhoneNumber) final;
    void BTS_handleCallAccept(common::PhoneNumber phoneNumber) final;
    void BTS_handleCallDrop(common::PhoneNumber phoneNumber) final;
    void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber) final;

     // IUserEventsHandler interface
public:
    void USER_handleCallAccept(common::PhoneNumber) final;
    void USER_handleStartDial() final;
    void USER_handleCallRequest(common::PhoneNumber) final;
    void USER_handleCallDrop(common::PhoneNumber) final;
};

}

/*

    virtual void USER_handleCallAccept()=0;
    virtual void USER_handleStartDial()=0;
    virtual void USER_handleCallRequest(common::PhoneNumber)=0;
    virtual void USER_handleCallDrop(common::PhoneNumber) =0;

    virtual void BST_handleDisconnected() = 0;
    virtual void BTS_handleSib(common::BtsId) = 0;
    virtual void BTS_handleAttachAccept() = 0;
    virtual void BTS_handleAttachReject() = 0;
    virtual void BTS_handleCallRequest(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleCallAccept(common::PhoneNumber receiverPhoneNumber)=0;
    virtual void BTS_handleCallDrop(common::PhoneNumber receiverPhoneNumber)=0;
*/
