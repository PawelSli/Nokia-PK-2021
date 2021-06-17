#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;

    MOCK_METHOD(void, handleSendMessage, (Sms& sms), (final));
    MOCK_METHOD(void, handleShowAllMessages, (), (final));
    MOCK_METHOD(void, handleSmsCreate, (), (final));
    MOCK_METHOD(void, handleShowMessage, (int index), (final));
    MOCK_METHOD(void, USER_handleCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, USER_handleStartDial, (), (final));
    MOCK_METHOD(void, USER_handleCallRequest, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_handleCallDrop, (), (final));
    MOCK_METHOD(void, handleSendTalkMessage, (const std::string), (final));
    
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showSmsReceivedNotification, (), (final));
    MOCK_METHOD(void, showSmsToCreate, (), (final));
    MOCK_METHOD(void, showAllMessages, (const std::vector<Sms>&), (final));
    MOCK_METHOD(void, showMessage, (Sms sms, bool areAllMessagesRead), (final));
    MOCK_METHOD(void, USER_showNotConnected, (), (final));
    MOCK_METHOD(void, USER_showConnecting, (), (final));
    MOCK_METHOD(void, USER_showConnected, (), (final));
    MOCK_METHOD(void, USER_showCallRequest, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_callAchieved, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_showPartnerNotAvailable, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_showPartnerDoesNotExist, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_startTalking, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_showStartMenu,(), (final));
    MOCK_METHOD(void, USER_showEnterPhoneNumber, (), (final));
    MOCK_METHOD(void, USER_showDialing, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, showCallView, (const std::string), (final));
    MOCK_METHOD(void, showcallDropping, (common::PhoneNumber), (final));
    
};

}

