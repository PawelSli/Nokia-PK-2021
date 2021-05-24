#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"
#include "ISmsDb.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer,
                ISmsDb& smsDb);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleReceivedMessage(Sms& sms) override;
    void handleSmsToUnknownRecipient() override;

<<<<<<< HEAD
    // IUserEventsHandler
=======
    // IUserEventsHandler interface
>>>>>>> 389db2ff21770a3cf47ddc6c816eeae2026030fc
    void handleSendMessage(Sms& sms) override;
    void handleShowAllMessages() override;
    void handleSmsCreate() override;
    void handleShowMessage(int index) override;

private:
    Context context;
    common::PrefixedLogger logger;

};

}
