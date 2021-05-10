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
};

}

/*
 * class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void BST_handleDisconnected() = 0;
    virtual void BTS_handleSib(common::BtsId) = 0;
    virtual void BTS_handleAttachAccept() = 0;
    virtual void BTS_handleAttachReject() = 0;
    virtual void BTS_handleCallRequest(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleUknownRecipient(common::PhoneNumber phoneNumber)=0;
    virtual void BTS_handleCallAccept(common::PhoneNumber receiverPhoneNumber)=0;
    virtual void BTS_handleCallDrop(common::PhoneNumber receiverPhoneNumber)=0;

};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void BTS_sendAttachRequest(common::BtsId) = 0;
    virtual void BTS_sendCallAccept(common::PhoneNumber)=0;
    virtual void BTS_sendCallDrop(common::PhoneNumber)=0;
    virtual void BTS_sendCallRequest(common::PhoneNumber)=0;

};

}

 */
