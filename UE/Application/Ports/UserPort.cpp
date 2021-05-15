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
    menu.addSelectionListItem("Call someone","");
    gui.setAcceptCallback([&](){
        switch (menu.getCurrentItemIndex().second) {
            case 2:
                USER_showEnterPhoneNumber();
                break;
        }
    });
}

void UserPort::USER_showCallRequest(common::PhoneNumber senderPhoneNumber)
{
    auto& alertMode=gui.setAlertMode();
    alertMode.setText("Call from: "+to_string(senderPhoneNumber));
    auto accept=[&,senderPhoneNumber](){
        handler->USER_handleCallAccept(senderPhoneNumber);
    };
    auto reject=[&,senderPhoneNumber](){
        handler->USER_handleCallDrop(senderPhoneNumber);
    };
    gui.setAcceptCallback(accept);
    gui.setRejectCallback(reject);

}

void UserPort::USER_callAchieved(common::PhoneNumber senderPhoneNumber)
{
    logger.logDebug("Talking mode with: ",senderPhoneNumber);
    IUeGui::ICallMode& callMode = gui.setCallMode();
    callMode.appendIncomingText("Call from: "+to_string(senderPhoneNumber));

}

void UserPort::USER_startTalking(common::PhoneNumber)
{
    IUeGui::ICallMode& callView = gui.setCallMode();
    callView.appendIncomingText("");
    gui.setAcceptCallback([&](){handler ->
                handleSendTalkMessage(callView.getOutgoingText());
                callView.clearOutgoingText();
    });
    gui.setRejectCallback(nullptr);
    //auto& callv = gui.setCallMode();
    //callv.appendIncomingText("");
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
    menu.addSelectionListItem("Call someone","");
    gui.setAcceptCallback([&](){
        switch (menu.getCurrentItemIndex().second) {
            case 2:
                USER_showEnterPhoneNumber();
                break;
        }
    });
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
    IUeGui::ITextMode& dialModeMenu = gui.setAlertMode();
    dialModeMenu.setText("Trying to\nconnect with:\n"+to_string(senderPhoneNumber));
    gui.setAcceptCallback([&](){});
    gui.setRejectCallback([&](){
        handler->USER_handleCallDrop(senderPhoneNumber);
        USER_showStartMenu();
    });
}

void UserPort::showCallView(const std::string inTxt)
{
    IUeGui::ICallMode& callView = gui.setCallMode();
    callView.appendIncomingText(inTxt);
    gui.setAcceptCallback([&](){handler ->
                handleSendTalkMessage(callView.getOutgoingText());
                callView.clearOutgoingText();
    });
    gui.setRejectCallback(nullptr);

}

}
