#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleSmsReceived(common::PhoneNumber number, std::string message);

    // IBtsEventsHandler interface
public:
    void handleDisconnected() final;
};

}
