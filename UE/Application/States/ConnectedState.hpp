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
    void handleReceivedMessage(Sms& incomingSms);

    // IBtsEventsHandler interface
    void BST_handleDisconnected() final;
    void BTS_handleCallRequest(common::PhoneNumber) final;
    void BTS_handleCallAccept(common::PhoneNumber phoneNumber) final;
    void BTS_handleCallDrop(common::PhoneNumber phoneNumber) final;
    void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber) final;

    void handleSmsToUnknownRecipient() final;

    // IUserEventsHandler interface

    void handleSendMessage(Sms& sms) final;
    void handleShowAllMessages() final;
    void handleSmsCreate() final;
    void handleShowMessage(int index) final;
    void USER_handleCallAccept(common::PhoneNumber) final;
    void USER_handleStartDial() final;
    void USER_handleCallRequest(common::PhoneNumber) final;
    void USER_handleCallDrop(common::PhoneNumber) final;
};

}

