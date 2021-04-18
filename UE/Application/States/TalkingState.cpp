#include "TalkingState.hpp"
#include "ConnectedState.hpp"
#include <thread>

namespace ue {


TalkingState::TalkingState(Context &context,common::PhoneNumber phoneNumber)
: BaseState(context, "TalkingState")
{
    context.user.talk(phoneNumber);
    using namespace std::chrono_literals;
    context.timer.startTimer();
}

void TalkingState::handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    context.timer.stopTimer();
    context.user.showPartnerNotAvailable(recipientPhoneNumber);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    context.user.showStartMenu();
    context.setState<ConnectedState>();
}

}

