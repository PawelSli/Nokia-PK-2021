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
    void handleDisconnected() final;
    void handleCallRequest() final;

     // IUserEventsHandler interface
public:
    void handleCallAccepted() final;
    void handleCallRejected() final;
};

}
