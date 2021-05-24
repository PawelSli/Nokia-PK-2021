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
    void handleReceivedMessage(Sms& incomingSms);

    // IBtsEventsHandler interface
    void handleDisconnected() final;
    void handleSmsToUnknownRecipient() final;

    // IUserEventsHandler interface

    void handleSendMessage(Sms& sms) final;
    void handleShowAllMessages() final;
    void handleSmsCreate() final;
    void handleShowMessage(int index) final;
};

}
