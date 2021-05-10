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

    MOCK_METHOD(void, USER_handleCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, USER_handleStartDial, (), (final));
    MOCK_METHOD(void, USER_handleCallRequest, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_handleCallDrop, (common::PhoneNumber), (final));

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, USER_showNotConnected, (), (final));
    MOCK_METHOD(void, USER_showConnecting, (), (final));
    MOCK_METHOD(void, USER_showConnected, (), (final));
    MOCK_METHOD(void, USER_showCallRequest, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_callAchieved, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_showPartnerNotAvailable, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_startTalking, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, USER_showStartMenu,(), (final));
    MOCK_METHOD(void, USER_showEnterPhoneNumber, (), (final));
    MOCK_METHOD(void, USER_showDialing, (common::PhoneNumber phoneNumber), (final));
};

}

/*
class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void USER_handleCallAccept()=0;
    virtual void USER_handleCallDropReceiver()=0;
    virtual void USER_handleStartDial()=0;
    virtual void USER_handleCallRequest(common::PhoneNumber)=0;
    virtual void USER_handleCallDropSender(common::PhoneNumber) =0;




};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void USER_showNotConnected() = 0;
    virtual void USER_showConnecting() = 0;
    virtual void USER_showConnected() = 0;
    virtual void USER_showCallRequest(common::PhoneNumber)=0;
    virtual void USER_talk(common::PhoneNumber)=0;
    virtual void USER_showPartnerNotAvailable(common::PhoneNumber)=0;
    virtual void USER_showStartMenu()=0;
    virtual void USER_showEnterPhoneNumber()=0;
    virtual void USER_showDialing(common::PhoneNumber)=0;
};

*/
