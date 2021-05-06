#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{}

void BtsPort::start(IBtsEventsHandler &handler)
{
    transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
    transport.registerDisconnectedCallback([this]() {handleDisconnected();});
    this->handler = &handler;
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    transport.registerDisconnectedCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleDisconnected()
{
    handler->BST_handleDisconnected();
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
        case common::MessageId::Sib:
        {
            auto btsId = reader.readBtsId();
            handler->BTS_handleSib(btsId);
            break;
        }
        case common::MessageId::AttachResponse:
        {
            bool accept = reader.readNumber<std::uint8_t>() != 0u;
            if (accept)
                handler->BTS_handleAttachAccept();
            else
                handler->BTS_handleAttachReject();
            break;
        }
        case common::MessageId::CallRequest:
        {
            handler->BTS_handleCallRequest(from);
            break;
        }
        case common::MessageId::UnknownRecipient:
        {
            handler->BTS_handleUknownRecipient(from);
            break;
        }
        default:
            logger.logError("unknow message: ", msgId, ", from: ", from);

        }
    }
    catch (std::exception const& ex)
    {
        logger.logError("handleMessage error: ", ex.what());
    }
}


void BtsPort::BTS_sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());


}

void BtsPort::BTS_sendCallAccept(common::PhoneNumber receiverPhoneNumber)
{
    logger.logDebug("sendCallAccept: ",receiverPhoneNumber);
    common::OutgoingMessage msg{common::MessageId::CallAccepted,
                               phoneNumber,
                               receiverPhoneNumber};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::BTS_sendCallDropFromReceiver(common::PhoneNumber receiverPhoneNumber)
{
    logger.logDebug("sendCallDrop: ",receiverPhoneNumber);
    common::OutgoingMessage msg{common::MessageId::CallDropped,
                               phoneNumber,
                               receiverPhoneNumber};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::BTS_sendCallRequest(common::PhoneNumber receiverPhoneNumber)
{
    logger.logDebug("sendCallDrop: ",receiverPhoneNumber);
    common::OutgoingMessage msg{common::MessageId::CallRequest,
                               phoneNumber,
                               receiverPhoneNumber};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::BTS_sendCallDropFromCaller(common::PhoneNumber receiverPhoneNumber)
{
    logger.logDebug("sendCallDropFromCaller: ",receiverPhoneNumber);
    common::OutgoingMessage msg{common::MessageId::CallDropped,
                               phoneNumber,
                               receiverPhoneNumber};
    transport.sendMessage(msg.getMessage());
}

}
