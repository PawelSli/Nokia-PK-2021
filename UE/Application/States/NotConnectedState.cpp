#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"

namespace ue
{

NotConnectedState::NotConnectedState(Context &context)
    : BaseState(context, "NotConnectedState")
{
    context.user.USER_showNotConnected();
}

void NotConnectedState::BTS_handleSib(common::BtsId btsId)
{
    context.setState<ConnectingState>(btsId);
}

}

