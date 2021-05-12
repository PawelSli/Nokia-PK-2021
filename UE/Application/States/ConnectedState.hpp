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
    void handleReceivedSms(common::PhoneNumber senderPhoneNumber, std::string message);

    // IBtsEventsHandler interface
public:
    void handleDisconnected() final;
};

}
