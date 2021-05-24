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
};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showSmsReceivedNotification, (), (final));
    MOCK_METHOD(void, showSmsToCreate, (), (final));
    MOCK_METHOD(void, showAllMessages, (const std::vector<Sms>&), (final));

};

}
