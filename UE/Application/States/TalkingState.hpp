#pragma once
#include "BaseState.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{
class TalkingState: public BaseState
{
private:
    common::PhoneNumber caller;
public:
    TalkingState(Context& context, common::PhoneNumber caller);
// IBtsEventsHandler interface
    void BTS_handleUknownRecipient(common::PhoneNumber) override;
    void handleTalkMessage(const std::string) final;

    void handleSendTalkMessage(const std::string) final;
    void BTS_handleCallDrop(common::PhoneNumber receiver) override;
    void USER_handleCallDrop(common::PhoneNumber callingPhoneNumber) override;
};

}
