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

    void BTS_sendAttachRequest(common::BtsId) override;
    void BTS_sendCallAccept(common::PhoneNumber) override;
    void BTS_sendCallDrop(common::PhoneNumber) override;
    void BTS_sendCallRequest(common::PhoneNumber) override;

private:
    void handleDisconnected();
    void handleMessage(BinaryMessage msg);

    common::PrefixedLogger logger;
    common::ITransport& transport;
    common::PhoneNumber phoneNumber;

    IBtsEventsHandler* handler = nullptr;
};

}
