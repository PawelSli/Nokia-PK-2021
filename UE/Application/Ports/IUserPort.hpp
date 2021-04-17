#pragma once
#include "Messages/PhoneNumber.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void callAccept()=0;
    virtual void callReject()=0;


};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showCallRequest()=0;
    virtual void talk()=0;
    virtual void showPartnerNotAvailable(common::PhoneNumber)=0;
    virtual void showStartMenu()=0;
};

}
