#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    void USER_showNotConnected() override;
    void USER_showConnecting() override;
    void USER_showConnected() override;

    void USER_showCallRequest(common::PhoneNumber) override;
    void USER_callAchieved(common::PhoneNumber) override;
    void USER_startTalking(common::PhoneNumber) override;
    void USER_showPartnerNotAvailable(common::PhoneNumber) override;
    void USER_showStartMenu() override;
    void USER_showEnterPhoneNumber() override;
    void USER_showDialing(common::PhoneNumber) override;

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
};

}
