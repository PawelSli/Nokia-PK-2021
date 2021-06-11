#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <chrono>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Mocks/ISmsDbMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Messages/BtsId.hpp"
#include "Sms.hpp"
#include <memory>
#include "SmsDb.hpp"

namespace ue
{
using namespace ::testing;
using namespace std::chrono_literals;

class ApplicationTestSuite : public Test
{
protected:
    const common::BtsId BTS_ID{42};
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::PhoneNumber SENDER_PHONE_NUMBER{113};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsPortMock> btsPortMock;
    StrictMock<IUserPortMock> userPortMock;
    StrictMock<ITimerPortMock> timerPortMock;
    StrictMock<ISmsDbMock> smsDbMock;


    Expectation expectShowNotConnected = EXPECT_CALL(userPortMock, USER_showNotConnected());
    Application objectUnderTest{PHONE_NUMBER,
                                loggerMock,
                                btsPortMock,
                                userPortMock,
                                timerPortMock,
                                smsDbMock};
    SmsDb smsDbUnderTest;
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{};

struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite
{
    ApplicationConnectingTestSuite();
    void doConnecting();
};

ApplicationConnectingTestSuite::ApplicationConnectingTestSuite()
{
    doConnecting();
}

void ApplicationConnectingTestSuite::doConnecting()
{
    EXPECT_CALL(userPortMock, USER_showConnecting());
    EXPECT_CALL(btsPortMock, BTS_sendAttachRequest(BTS_ID));
    EXPECT_CALL(timerPortMock, TIMER_startTimer(0.5,1));
    objectUnderTest.BTS_handleSib(BTS_ID);
}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachRequestOnSib)
{
    // everything in constructor
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachReject)
{
    EXPECT_CALL(userPortMock, USER_showNotConnected());
    EXPECT_CALL(timerPortMock, TIMER_stopTimer(1));
    objectUnderTest.BTS_handleAttachReject();
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachTimeout)
{
    EXPECT_CALL(userPortMock, USER_showNotConnected());
    objectUnderTest.TIMER_handleTimeout();
}

struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
{
    ApplicationConnectedTestSuite();
    void doConnected();
};

ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
{
    doConnected();
}

void ApplicationConnectedTestSuite::doConnected()
{

    EXPECT_CALL(timerPortMock, TIMER_stopTimer(1));
    EXPECT_CALL(userPortMock, USER_showConnected());
    objectUnderTest.BTS_handleAttachAccept();
}

TEST_F(ApplicationConnectedTestSuite, shallShowConnectedOnAttachAccept)
{
    // see test-suite constructor
}

TEST_F(ApplicationConnectedTestSuite, shallShowNotConnectedOnDisconnectFromBts)
{
    EXPECT_CALL(userPortMock, USER_showNotConnected());
    objectUnderTest.BST_handleDisconnected();
}

TEST_F(ApplicationConnectedTestSuite, shallReattach)
{

    EXPECT_CALL(userPortMock, USER_showNotConnected());
    objectUnderTest.BST_handleDisconnected();

    doConnecting();
    doConnected();
}


TEST_F(ApplicationConnectedTestSuite, shallHandleReceivedMessage)
{
    Sms receivedMessage{PHONE_NUMBER, PHONE_NUMBER, "message", false, false, false};
    EXPECT_CALL(smsDbMock, addMessage(receivedMessage));
    EXPECT_CALL(userPortMock, showSmsReceivedNotification());
    objectUnderTest.handleReceivedMessage(receivedMessage);
}

TEST_F(ApplicationConnectedTestSuite, shallAddReceivedMessage)
{
    Sms receivedMessage{PHONE_NUMBER, PHONE_NUMBER, "rec message", false, false, false};
    smsDbUnderTest.addMessage(receivedMessage);
    Sms* smsToAssert = smsDbUnderTest.getMessage(0);
    ASSERT_EQ(receivedMessage, *smsToAssert);
}
  
TEST_F(ApplicationConnectedTestSuite,shallHandleCalllRequest)
{
    EXPECT_CALL(userPortMock,USER_showCallRequest(_));
    EXPECT_CALL(timerPortMock,TIMER_startTimerAndDoSomething(_,30,2));
    objectUnderTest.BTS_handleCallRequest(SENDER_PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleCallRejectFromReceiver)
{
    EXPECT_CALL(timerPortMock,TIMER_stopTimer(2));
    EXPECT_CALL(btsPortMock,BTS_sendCallDrop(SENDER_PHONE_NUMBER));
    EXPECT_CALL(userPortMock,USER_showConnected());
    objectUnderTest.USER_handleCallDrop(SENDER_PHONE_NUMBER);

}

TEST_F(ApplicationConnectedTestSuite,shallHandleCallDropFromSender)
{
    EXPECT_CALL(timerPortMock,TIMER_stopTimer(2));
    EXPECT_CALL(userPortMock,USER_showPartnerNotAvailable(_));
    EXPECT_CALL(timerPortMock,TIMER_startTimerAndDoSomething(_,2,2));
    objectUnderTest.BTS_handleCallDrop(SENDER_PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleUknownRecipient)
{
    EXPECT_CALL(timerPortMock,TIMER_stopTimer(2));
    EXPECT_CALL(userPortMock,USER_showPartnerNotAvailable(_));
    EXPECT_CALL(timerPortMock,TIMER_startTimerAndDoSomething(_,2,2));
    objectUnderTest.BTS_handleUknownRecipient(SENDER_PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleStartDial)
{
    EXPECT_CALL(userPortMock,USER_showEnterPhoneNumber());
    objectUnderTest.USER_handleStartDial();
}

TEST_F(ApplicationConnectedTestSuite,shallHandleSendCallRequest)
{
    EXPECT_CALL(btsPortMock,BTS_sendCallRequest(SENDER_PHONE_NUMBER));
    EXPECT_CALL(timerPortMock,TIMER_startTimerAndDoSomething(_,60,2));
    EXPECT_CALL(userPortMock,USER_showDialing(SENDER_PHONE_NUMBER));
    objectUnderTest.USER_handleCallRequest(SENDER_PHONE_NUMBER);
}

struct ApplicationTalkingTestSuite : ApplicationConnectedTestSuite
{
    ApplicationTalkingTestSuite();
    void doTalking();
};

ApplicationTalkingTestSuite::ApplicationTalkingTestSuite()
{
    doTalking();
}

void ApplicationTalkingTestSuite::doTalking()
{
    EXPECT_CALL(timerPortMock,TIMER_stopTimer(2));
    EXPECT_CALL(btsPortMock,BTS_sendCallAccept(_));
    EXPECT_CALL(userPortMock,USER_callAchieved(_));
    EXPECT_CALL(timerPortMock,TIMER_startTimerAndDoSomething(_,180,3));
    EXPECT_CALL(userPortMock,USER_startTalking(SENDER_PHONE_NUMBER));
    objectUnderTest.USER_handleCallAccept(SENDER_PHONE_NUMBER);
}

TEST_F(ApplicationTalkingTestSuite,shallHandleUknownRecipient)
{
    EXPECT_CALL(timerPortMock,TIMER_stopTimer(3));
    EXPECT_CALL(userPortMock,USER_showPartnerNotAvailable(_));
    EXPECT_CALL(timerPortMock,TIMER_startTimerAndDoSomething(_,2,3));
    objectUnderTest.BTS_handleUknownRecipient(SENDER_PHONE_NUMBER);
}

}









