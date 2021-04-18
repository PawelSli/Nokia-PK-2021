#pragma once
#include "BaseState.hpp"

namespace ue
{
class TalkingState: public BaseState
{
public:
    TalkingState(Context& context, common::PhoneNumber phoneNumber);

// IBtsEventsHandler interface
public:
    void handleUknownRecipient(common::PhoneNumber) final;
};

}
