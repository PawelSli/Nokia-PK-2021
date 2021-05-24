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

<<<<<<< HEAD

    //IUserEventsHandler
=======
    // IUserEventsHandler interface
>>>>>>> 389db2ff21770a3cf47ddc6c816eeae2026030fc
    void handleSendMessage(Sms& sms) final;
    void handleShowAllMessages() final;
    void handleSmsCreate() final;
    void handleShowMessage(int index) final;
};

}
