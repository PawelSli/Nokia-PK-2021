#pragma once
#include "../Sms.hpp"
#include <vector>

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleSendMessage(Sms& sms) = 0;
    virtual void handleShowAllMessages() = 0;
    virtual void handleSmsCreate() = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showSmsReceivedNotification() = 0;
    virtual void showSmsToCreate() = 0;
    virtual void showAllMessages(const std::vector<Sms>& messages) = 0;
};

}
