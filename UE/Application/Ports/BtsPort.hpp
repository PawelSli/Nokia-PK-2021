#pragma once

#include "IBtsPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "ITransport.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class BtsPort : public IBtsPort
{
public:
    BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber);
    void start(IBtsEventsHandler& handler);
    void stop();
    common::PhoneNumber getPhoneNumber() override;

    void BTS_sendAttachRequest(common::BtsId) override;
    void BTS_sendCallAccept(common::PhoneNumber) override;
    void BTS_sendCallDrop(common::PhoneNumber) override;
    void BTS_sendCallRequest(common::PhoneNumber) override;
    void sendTalkMessage(const std::string, common::PhoneNumber) override;

    void sendMessage(Sms& sms);

    void sendMessage(Sms& sms);

private:
    void handleDisconnected();
    void handleMessage(BinaryMessage msg);

    common::PrefixedLogger logger;
    common::ITransport& transport;
    common::PhoneNumber phoneNumber;

    IBtsEventsHandler* handler = nullptr;
};

}
