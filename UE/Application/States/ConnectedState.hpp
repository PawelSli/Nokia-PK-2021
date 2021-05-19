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
    void handleReceivedMessage(Sms incomingSms);

    // IBtsEventsHandler interface
public:
    void handleDisconnected() final;
};

}
