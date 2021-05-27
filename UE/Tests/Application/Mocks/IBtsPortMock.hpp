#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, BST_handleDisconnected, (), (final));
    MOCK_METHOD(void, BTS_handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, BTS_handleAttachAccept, (), (final));
    MOCK_METHOD(void, BTS_handleAttachReject, (), (final));
    MOCK_METHOD(void, BTS_handleCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, BTS_handleUknownRecipient, (common::PhoneNumber), (final));
    MOCK_METHOD(void, BTS_handleCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, BTS_handleCallDrop, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleTalkMessage, (const std::string), (final));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, BTS_sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, BTS_sendCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, BTS_sendCallDrop, (common::PhoneNumber), (final));
    MOCK_METHOD(void, BTS_sendCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendTalkMessage, (const std::string, common::PhoneNumber), (final));
    MOCK_METHOD(common::PhoneNumber, getPhoneNumber,(),(final));
};

}
