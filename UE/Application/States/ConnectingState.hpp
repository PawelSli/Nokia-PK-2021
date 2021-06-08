#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectingState : public BaseState
{
public:
    ConnectingState(Context& context, common::BtsId btsId);

    // ITimerEventsHandler interface
public:
    void TIMER_handleTimeout() final;

    // IBtsEventsHandler interface
public:
    void BTS_handleAttachAccept() final;
    void BTS_handleAttachReject() final;
};

}
