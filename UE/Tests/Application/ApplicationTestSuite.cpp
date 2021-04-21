#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <chrono>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Messages/BtsId.hpp"
#include <memory>

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

    Expectation expectShowNotConnected = EXPECT_CALL(userPortMock, showNotConnected());
    Application objectUnderTest{PHONE_NUMBER,
                                loggerMock,
                                btsPortMock,
                                userPortMock,
                                timerPortMock};
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
    EXPECT_CALL(userPortMock, showConnecting());
    EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
    EXPECT_CALL(timerPortMock, startTimer(500ms));
    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachRequestOnSib)
{
    // everything in constructor
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachReject)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachReject();
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachTimeout)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleTimeout();
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
    EXPECT_CALL(userPortMock, showConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachAccept();
}

TEST_F(ApplicationConnectedTestSuite, shallShowConnectedOnAttachAccept)
{
    // see test-suite constructor
}

TEST_F(ApplicationConnectedTestSuite, shallShowNotConnectedOnDisconnectFromBts)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();
}

TEST_F(ApplicationConnectedTestSuite, shallReattach)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();

    doConnecting();
    doConnected();
}

TEST_F(ApplicationConnectedTestSuite,shallHandleCallRequest)
{
    EXPECT_CALL(userPortMock,showCallRequest(_));
    EXPECT_CALL(timerPortMock,startTimer(30*1000ms));
    objectUnderTest.handleCallRequest(SENDER_PHONE_NUMBER);
}

TEST_F(ApplicationConnectedTestSuite,shallHandleCallReject)
{
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(btsPortMock,sendCallDrop(_));
    EXPECT_CALL(userPortMock,showStartMenu());
    objectUnderTest.handleCallRejected();

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
    EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(btsPortMock,sendCallAccept(_));
    EXPECT_CALL(userPortMock,talk(_));
    objectUnderTest.handleCallAccepted();
}

TEST_F(ApplicationTalkingTestSuite,shallHandleUknownRecipient)
{
    /*
     *  SECOND THING TO AKS IN THE CLASS : TIMER
     */
    //EXPECT_CALL(timerPortMock,stopTimer());
    EXPECT_CALL(userPortMock,showPartnerNotAvailable(_));
    EXPECT_CALL(userPortMock,showStartMenu());
    doConnected();
    objectUnderTest.handleUknownRecipient(SENDER_PHONE_NUMBER);
}

}
