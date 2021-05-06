#pragma once

#include "BaseState.hpp"

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
    //
    void BTS_handleCallAccept() final;
    void BTS_handleCallDrop() final;
    void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber) final;

     // IUserEventsHandler interface
public:
    void USER_handleCallAccept() final;
    void USER_handleCallDropReceiver() final;
    //
    void USER_handleStartDial() final;
    void USER_handleCallRequest(common::PhoneNumber) final;
    void USER_handleCallDropSender(common::PhoneNumber) final;
};

}
