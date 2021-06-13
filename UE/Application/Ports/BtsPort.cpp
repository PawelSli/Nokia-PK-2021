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
        case common::MessageId::CallDropped:
        {
            handler->BTS_handleCallDrop(from);
            break;
        }
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
        case common::MessageId::Sms:
        {
            Sms sms(from, to, reader.readRemainingText(), false, false, false);          
            handler->handleReceivedMessage(sms);
            break;
        }
        case common::MessageId::UnknownRecipient:
        {
            if (reader.readMessageId() == common::MessageId::Sms) {
                handler->handleSmsToUnknownRecipient();
            }else{
                handler->BTS_handleUknownRecipient(from);
            }
            break;
        }
        case common::MessageId::CallRequest:
        {
            handler->BTS_handleCallRequest(from);
            break;
        }
        case common::MessageId::CallTalk:
        {
            logger.logDebug("bts call talk ", from);
            handler->handleTalkMessage(reader.readRemainingText() );
            break;
        }
        case common::MessageId::CallAccepted:
        {
            handler->BTS_handleCallAccept(from);
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


common::PhoneNumber BtsPort::getPhoneNumber()
{
    return phoneNumber;
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

void BtsPort::sendMessage(Sms& sms)
{
    common::OutgoingMessage message(common::MessageId::Sms, sms.senderPhoneNumber, sms.receiverPhoneNumber);
    message.writeText(sms.message);
    transport.sendMessage(message.getMessage());
}

void BtsPort::BTS_sendCallAccept(common::PhoneNumber receiverPhoneNumber)
{
    logger.logDebug("sendCallAccept: ",receiverPhoneNumber);
    common::OutgoingMessage msg{common::MessageId::CallAccepted,
                               phoneNumber,
                               receiverPhoneNumber};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::BTS_sendCallDrop(common::PhoneNumber receiverPhoneNumber)
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

void BtsPort::sendTalkMessage(const std::string txt, common::PhoneNumber number)
{
    logger.logDebug("sendTalkMessage ",number);
    common::OutgoingMessage msg {common::MessageId::CallTalk,phoneNumber, number};
    msg.writeText(txt);
    transport.sendMessage(msg.getMessage());
}


}
