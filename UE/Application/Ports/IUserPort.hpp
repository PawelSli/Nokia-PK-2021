#pragma once
#include "Messages/PhoneNumber.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;

    virtual void USER_handleCallAccept(common::PhoneNumber)=0;
    virtual void USER_handleStartDial()=0;
    virtual void USER_handleCallRequest(common::PhoneNumber)=0;
    virtual void USER_handleCallDrop(common::PhoneNumber) =0;




};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

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
};

}
