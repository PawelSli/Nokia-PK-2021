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

    MOCK_METHOD(void, handleCallAccepted, (), (final));
    MOCK_METHOD(void, handleCallRejected, (), (final));

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showCallRequest, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, talk, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, showPartnerNotAvailable, (common::PhoneNumber phoneNumber), (final));
    MOCK_METHOD(void, showStartMenu,(), (final));
};

}
