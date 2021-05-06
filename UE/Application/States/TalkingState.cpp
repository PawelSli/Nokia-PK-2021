#include "TalkingState.hpp"
#include "ConnectedState.hpp"
#include <thread>

namespace ue {


TalkingState::TalkingState(Context &context,common::PhoneNumber phoneNumber)
    : BaseState(context, "TalkingState"), caller{phoneNumber}
{
    context.user.USER_talk(phoneNumber);
}

void TalkingState::BTS_handleUknownRecipient(common::PhoneNumber recipientPhoneNumber)
{
    context.timer.TIMER_stopTimer();
    context.user.USER_showPartnerNotAvailable(recipientPhoneNumber);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
    context.user.USER_showStartMenu();
    context.setState<ConnectedState>();
}

}

