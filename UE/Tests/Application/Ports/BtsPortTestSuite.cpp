#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/BtsPort.hpp"
#include "Messages/MessageHeader.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/ITransportMock.hpp"
#include "Messages/OutgoingMessage.hpp"
#include "Messages/IncomingMessage.hpp"
#include "SmsDb.hpp"
#include "Sms.hpp"

namespace ue
{
using namespace ::testing;

class BtsPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::BtsId BTS_ID{13121981ll};
    SmsDb DATABASE{};
    const common::PhoneNumber SENDER_PHONE_NUMBER{113};

    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsEventsHandlerMock> handlerMock;
    StrictMock<common::ITransportMock> transportMock;
    common::ITransport::MessageCallback messageCallback;
    common::ITransport::DisconnectedCallback disconnectCallback;

    BtsPort objectUnderTest{loggerMock, transportMock, PHONE_NUMBER};

    BtsPortTestSuite()
    {
        EXPECT_CALL(transportMock, registerMessageCallback(_))
                .WillOnce(SaveArg<0>(&messageCallback));
        EXPECT_CALL(transportMock, registerDisconnectedCallback(_))
                .WillOnce(SaveArg<0>(&disconnectCallback));
        objectUnderTest.start(handlerMock);
    }
    ~BtsPortTestSuite()
    {

        EXPECT_CALL(transportMock, registerMessageCallback(IsNull()));
        EXPECT_CALL(transportMock, registerDisconnectedCallback(IsNull()));
        objectUnderTest.stop();
    }
};

TEST_F(BtsPortTestSuite, shallRegisterHandlersBetweenStartStop)
{
}

TEST_F(BtsPortTestSuite, shallIgnoreWrongMessage)
{
    common::OutgoingMessage wrongMsg{};
    wrongMsg.writeBtsId(BTS_ID);
    messageCallback(wrongMsg.getMessage());
}

TEST_F(BtsPortTestSuite, shallHandleDisconnected)
{

    EXPECT_CALL(handlerMock, BST_handleDisconnected());
    disconnectCallback();
}

TEST_F(BtsPortTestSuite, shallHandleSib)
{
    EXPECT_CALL(handlerMock, BTS_handleSib(BTS_ID));
    common::OutgoingMessage msg{common::MessageId::Sib,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    msg.writeBtsId(BTS_ID);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite, shallHandleAttachAccept)
{
    EXPECT_CALL(handlerMock, BTS_handleAttachAccept());
    common::OutgoingMessage msg{common::MessageId::AttachResponse,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    msg.writeNumber(true);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite, shallHandleAttachReject)
{
    EXPECT_CALL(handlerMock, BTS_handleAttachReject());
    common::OutgoingMessage msg{common::MessageId::AttachResponse,
                                common::PhoneNumber{},
                                PHONE_NUMBER};
    msg.writeNumber(false);
    messageCallback(msg.getMessage());
}

TEST_F(BtsPortTestSuite, shallSendAttachRequest)
{
    common::BinaryMessage msg;
    EXPECT_CALL(transportMock, sendMessage(_)).WillOnce([&msg](auto param) { msg = std::move(param); return true; });
    objectUnderTest.BTS_sendAttachRequest(BTS_ID);
    common::IncomingMessage reader(msg);
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::AttachRequest, reader.readMessageId()) );
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(common::PhoneNumber{}, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(BTS_ID, reader.readBtsId()));
    ASSERT_NO_THROW(reader.checkEndOfMessage());
}


TEST_F(BtsPortTestSuite, shallSendSms)
{
    common::BinaryMessage msg;
    const auto senderPhone = common::PhoneNumber{1};
    const auto receiverPhone = common::PhoneNumber{2};
    std::string text = "text";
    bool readed = false;
    bool sended = false;
    bool failed = false;
    Sms sms = Sms(senderPhone,receiverPhone, text, readed, sended, failed);
    EXPECT_CALL(transportMock, sendMessage(_)).WillOnce([&msg](auto param) {msg = std::move(param); return true;});
    objectUnderTest.sendMessage(sms);
    common::IncomingMessage reader(msg);
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::Sms, reader.readMessageId()));
    ASSERT_NO_THROW(EXPECT_EQ(senderPhone, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(receiverPhone, reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(text, reader.readRemainingText()));
    ASSERT_NO_THROW(reader.checkEndOfMessage());
}


TEST_F(BtsPortTestSuite, shallHandleCallRequest)
{
    EXPECT_CALL(handlerMock,BTS_handleCallRequest(SENDER_PHONE_NUMBER));
    common::OutgoingMessage msg{common::MessageId::CallRequest,
                               SENDER_PHONE_NUMBER,
                               PHONE_NUMBER};
    messageCallback(msg.getMessage());

}

TEST_F(BtsPortTestSuite, shallSendCallAccept)
{
    common::BinaryMessage msg;
    EXPECT_CALL(transportMock, sendMessage(_)).WillOnce([&msg](auto param) { msg = std::move(param); return true; });
    objectUnderTest.BTS_sendCallAccept(SENDER_PHONE_NUMBER);
    common::IncomingMessage reader{msg};
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::CallAccepted,reader.readMessageId()));
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER,reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(SENDER_PHONE_NUMBER,reader.readPhoneNumber()));
    ASSERT_NO_THROW(reader.checkEndOfMessage());
}

TEST_F(BtsPortTestSuite, shallSendCallReject)
{
    common::BinaryMessage msg;
    EXPECT_CALL(transportMock, sendMessage(_)).WillOnce([&msg](auto param) { msg = std::move(param); return true; });
    objectUnderTest.BTS_sendCallDrop(SENDER_PHONE_NUMBER);
    common::IncomingMessage reader {msg};
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::CallDropped,reader.readMessageId()));
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER,reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(SENDER_PHONE_NUMBER,reader.readPhoneNumber()));
    ASSERT_NO_THROW(reader.checkEndOfMessage());
}

TEST_F(BtsPortTestSuite,shallHandleCallAcceptFromReceiver)
{
    EXPECT_CALL(handlerMock,BTS_handleCallAccept(SENDER_PHONE_NUMBER));
    common::OutgoingMessage msg{common::MessageId::CallAccepted,
                               SENDER_PHONE_NUMBER,
                               PHONE_NUMBER};
    messageCallback(msg.getMessage());

}

TEST_F(BtsPortTestSuite,shallHandleCallRejectFromReceiver)
{
    EXPECT_CALL(handlerMock,BTS_handleCallDrop(SENDER_PHONE_NUMBER));
    common::OutgoingMessage msg{common::MessageId::CallDropped,
                               SENDER_PHONE_NUMBER,
                               PHONE_NUMBER};
    messageCallback(msg.getMessage());

}

TEST_F(BtsPortTestSuite,shallSendCallRequest)
{
    common::BinaryMessage msg;
    EXPECT_CALL(transportMock, sendMessage(_)).WillOnce([&msg](auto param) { msg = std::move(param); return true; });
    objectUnderTest.BTS_sendCallRequest(SENDER_PHONE_NUMBER);
    common::IncomingMessage reader {msg};
    ASSERT_NO_THROW(EXPECT_EQ(common::MessageId::CallRequest,reader.readMessageId()));
    ASSERT_NO_THROW(EXPECT_EQ(PHONE_NUMBER,reader.readPhoneNumber()));
    ASSERT_NO_THROW(EXPECT_EQ(SENDER_PHONE_NUMBER,reader.readPhoneNumber()));
    ASSERT_NO_THROW(reader.checkEndOfMessage());
}

TEST_F(BtsPortTestSuite, shallSendTalkMessage)
{
    const std::string text = "text";
    EXPECT_CALL(transportMock, sendMessage(_));
    objectUnderTest.sendTalkMessage(text, PHONE_NUMBER);
}

}
