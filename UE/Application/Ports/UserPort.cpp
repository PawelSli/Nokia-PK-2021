#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "Sms.hpp"
#include <string>
#include <vector>
#include "UeGui/ITextMode.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/ICallMode.hpp"

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
        switch(menu.getCurrentItemIndex().second){

            case 0: handler->handleSmsCreate();
            break;

            case 1: handler->handleShowAllMessages();
            break;
            
            case 2: USER_showEnterPhoneNumber();
            break;
        }
    });
}

void UserPort::showSmsReceivedNotification()
{
    gui.showNewSms();
}

void UserPort::showSmsToCreate()
{
    IUeGui::ISmsComposeMode& createSms = gui.setSmsComposeMode();
    gui.setAcceptCallback([&](){
        Sms messageToSend{phoneNumber, createSms.getPhoneNumber(), createSms.getSmsText(), false, true, false};
        handler->handleSendMessage(messageToSend);
        createSms.clearSmsText();
        USER_showConnected();
    });

    gui.setRejectCallback([&](){
        createSms.clearSmsText();
        USER_showConnected();
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

void UserPort::USER_startTalking(common::PhoneNumber tmp)
{
    IUeGui::ICallMode& callView = gui.setCallMode();
    callView.appendIncomingText("");
    anotherPhoneNumber = tmp;
    gui.setAcceptCallback([&](){handler ->
                handleSendTalkMessage(callView.getOutgoingText());
                callView.clearOutgoingText();
    });

    gui.setRejectCallback([&](){
        handler->USER_handleCallDrop(tmp);
    });
}

void UserPort::showAllMessages(const std::vector<Sms>& messages)
{
    auto& listViewMode = gui.setListViewMode();
    listViewMode.clearSelectionList();

    for (auto& message : messages)
    {
        if (message.senderPhoneNumber == phoneNumber)
        {
            if(message.failed){
                listViewMode.addSelectionListItem("TO " + to_string(message.receiverPhoneNumber) + " (FAILED)", "");
            } else{
                listViewMode.addSelectionListItem("TO " + to_string(message.receiverPhoneNumber), "");
            }
        } else {
            if (!message.read) {
                listViewMode.addSelectionListItem("FROM " + to_string(message.senderPhoneNumber) + " (*)", "");
            } else {
                listViewMode.addSelectionListItem("FROM " + to_string(message.senderPhoneNumber), "");
            }
        }

    }

    gui.setRejectCallback([this]{
        USER_showConnected();
    });

    gui.setAcceptCallback([this, &listViewMode](){
        handler->handleShowMessage(listViewMode.getCurrentItemIndex().second);
    });
}

void UserPort::showMessage(Sms message, bool areAllMessagesRead)
{
    if(areAllMessagesRead)
    {
        // disable new message notification
    }

    auto& textViewMode = gui.setViewTextMode();
    textViewMode.setText(message.message);

    gui.setRejectCallback([this](){
        handler->handleShowAllMessages();
    });
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
    gui.setRejectCallback([&](){
        handler->USER_handleCallDrop(anotherPhoneNumber);
    });

}

void UserPort::showcallDropping(common::PhoneNumber callingPhoneNumber)
{
    auto& callingView = gui.setAlertMode();
    callingView.setText("Phone nr: " + to_string(callingPhoneNumber) + "\n dropped the call");
}

}
