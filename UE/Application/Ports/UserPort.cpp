#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/ICallMode.hpp"
#include "UeGui/ITextMode.hpp"
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

void UserPort::USER_showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::USER_showConnecting()
{
    gui.showConnecting();
}

void UserPort::USER_showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
}

void UserPort::USER_showCallRequest(common::PhoneNumber senderPhoneNumber)
{
    IUeGui::IDialMode& dialMode=gui.setDialMode();
    logger.logDebug("Call from : ",senderPhoneNumber);
    auto accept=[&](){
        handler->USER_handleCallAccept();
    };
    auto reject=[&](){
        handler->USER_handleCallDropReceiver();
    };
    gui.setAcceptCallback(accept);
    gui.setRejectCallback(reject);

}

void UserPort::USER_talk(common::PhoneNumber senderPhoneNumber)
{
    logger.logDebug("Talking mode with: ",senderPhoneNumber);
    IUeGui::ICallMode& callMode = gui.setCallMode();
    //TO IMPLEMENT
}

void UserPort::USER_showPartnerNotAvailable(common::PhoneNumber receiverPhoneNumber)
{
    gui.showPeerUserNotAvailable(receiverPhoneNumber);
}

void UserPort::USER_showStartMenu()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
}

void UserPort::USER_showEnterPhoneNumber()
{
    ue::IUeGui::IDialMode& dialModeMenu = gui.setDialMode();
    gui.setAcceptCallback([&](){
        handler->USER_handleCallRequest(dialModeMenu.getPhoneNumber());
    });
    gui.setRejectCallback([&](){
        USER_showStartMenu();
    });

}

void UserPort::USER_showDialing(common::PhoneNumber senderPhoneNumber){
    logger.logDebug("Trying to connect with: ",senderPhoneNumber);
    auto& dialModeMenu = gui.setAlertMode();
    dialModeMenu.setText("Trying to connect with... ");
    gui.setAcceptCallback([&](){});
    gui.setRejectCallback([&](){
        USER_showStartMenu();
    });
}

}
