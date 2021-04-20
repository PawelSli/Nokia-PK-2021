#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ICallMode.hpp"
#include <string>

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
}

void UserPort::showCallRequest(common::PhoneNumber senderPhoneNumber)
{
    IUeGui::ICallMode& callMode=gui.setCallMode();
    callMode.appendIncomingText("Call from: " + to_string(senderPhoneNumber));
    auto accept=[&](){
        handler->handleCallAccepted();
    };
    auto reject=[&](){
        handler->handleCallRejected();
    };
    gui.setAcceptCallback(accept);
    gui.setRejectCallback(reject);

}

void UserPort::talk(common::PhoneNumber senderPhoneNumber)
{
    logger.logDebug("Talking mode with: ",senderPhoneNumber);
    //TO IMPLEMENT
}

void UserPort::showPartnerNotAvailable(common::PhoneNumber receiverPhoneNumber)
{
    gui.showPeerUserNotAvailable(receiverPhoneNumber);
}

void UserPort::showStartMenu()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
}

}
