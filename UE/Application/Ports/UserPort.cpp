#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "Sms.hpp"
#include <string>
#include <vector>

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

            case 0: showSmsToCreate();
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
            listViewMode.addSelectionListItem("[TO] " + to_string(message.receiverPhoneNumber), message.message);
        } else
        {
            if(!message.read)
            {
                listViewMode.addSelectionListItem("[FROM] " + to_string(message.senderPhoneNumber), message.message + "NOT READ!");
            } else
            {
                listViewMode.addSelectionListItem("[FROM] " + to_string(message.senderPhoneNumber), message.message);
            }
        }

    }
}



}
