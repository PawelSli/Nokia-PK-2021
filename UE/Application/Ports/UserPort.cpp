#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "Sms.hpp"
#include <string>
#include <vector>
#include "UeGui/ITextMode.hpp"

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
    gui.setAcceptCallback([&](){
        switch(menu.getCurrentItemIndex().second){

            case 0: handler->handleSmsCreate();
            break;

            case 1: handler->handleShowAllMessages();
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
        showConnected();
    });

    gui.setRejectCallback([&](){
        createSms.clearSmsText();
        showConnected();
    });
}


void UserPort::showAllMessages(const std::vector<Sms>& messages)
{

    auto& listViewMode = gui.setListViewMode();
    listViewMode.clearSelectionList();

    for(auto& message : messages)
    {
        if(message.senderPhoneNumber == phoneNumber)
        {
            if(message.failed){
                listViewMode.addSelectionListItem("TO " + to_string(message.receiverPhoneNumber) + " X", "");
            } else{
                listViewMode.addSelectionListItem("TO " + to_string(message.receiverPhoneNumber), "");
            }

        } else
        {
            if(!message.read)
            {
                listViewMode.addSelectionListItem("FROM " + to_string(message.senderPhoneNumber) + " (*)", "");
            } else
            {
                listViewMode.addSelectionListItem("FROM " + to_string(message.senderPhoneNumber), "");
            }
        }

    }

    gui.setRejectCallback([this]{
        showConnected();
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



}
