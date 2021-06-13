#pragma once
#include "../Sms.hpp"
#include <vector>
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void handleSendMessage(Sms& sms) = 0;
    virtual void handleShowAllMessages() = 0;
    virtual void handleSmsCreate() = 0;
    virtual void handleShowMessage(int index) = 0;

    virtual void USER_handleCallAccept(common::PhoneNumber)=0;
    virtual void USER_handleStartDial()=0;
    virtual void USER_handleCallRequest(common::PhoneNumber)=0;
    virtual void USER_handleCallDrop(common::PhoneNumber) =0;
    virtual void handleSendTalkMessage(const std::string)=0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showSmsReceivedNotification() = 0;
    virtual void showSmsToCreate() = 0;
    virtual void showAllMessages(const std::vector<Sms>& messages) = 0;
    virtual void showMessage(Sms message, bool areAllMessagesRead) = 0;
    virtual void USER_showNotConnected() = 0;
    virtual void USER_showConnecting() = 0;
    virtual void USER_showConnected() = 0;
    virtual void USER_showCallRequest(common::PhoneNumber)=0;
    virtual void USER_callAchieved(common::PhoneNumber)=0;
    virtual void USER_startTalking(common::PhoneNumber)=0;
    virtual void USER_showPartnerNotAvailable(common::PhoneNumber)=0;
    virtual void USER_showStartMenu()=0;
    virtual void USER_showEnterPhoneNumber()=0;
    virtual void USER_showDialing(common::PhoneNumber)=0;
    virtual void showCallView(const std::string)=0;
    virtual void showcallDropping(common::PhoneNumber) = 0;
};

}
