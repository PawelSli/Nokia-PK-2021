#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/UserPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IUeGuiMock.hpp"

namespace ue
{
using namespace ::testing;

class UserPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::PhoneNumber SENDER_PHONE_NUMBER{113};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IUserEventsHandlerMock> handlerMock;
    StrictMock<IUeGuiMock> guiMock;
    StrictMock<IListViewModeMock> listViewModeMock;
    StrictMock<IDialModeMock> dialModeMock;
    StrictMock<ICallModeMock> callModeMock;
    StrictMock<ITextModeMock> textModeMock;


    UserPort objectUnderTest{loggerMock, guiMock, PHONE_NUMBER};

    UserPortTestSuite()
    {
        EXPECT_CALL(guiMock, setTitle(HasSubstr(to_string(PHONE_NUMBER))));
        objectUnderTest.start(handlerMock);
    }
    ~UserPortTestSuite()
    {
        objectUnderTest.stop();
    }
};

TEST_F(UserPortTestSuite, shallStartStop)
{
}

TEST_F(UserPortTestSuite, shallShowNotConnected)
{
    EXPECT_CALL(guiMock, showNotConnected());
    objectUnderTest.USER_showNotConnected();
}

TEST_F(UserPortTestSuite, shallShowConnecting)
{
    EXPECT_CALL(guiMock, showConnecting());
    objectUnderTest.USER_showConnecting();
}

TEST_F(UserPortTestSuite, shallShowMenuOnConnected)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(3);
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    objectUnderTest.USER_showConnected();
}

TEST_F(UserPortTestSuite,shallShowCallRequest)
{
    EXPECT_CALL(guiMock, setAlertMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock,setText(_));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    objectUnderTest.USER_showCallRequest(PHONE_NUMBER);
}

TEST_F(UserPortTestSuite,shallTalk)
{
    EXPECT_CALL(guiMock,setCallMode()).WillOnce(ReturnRef(callModeMock));
    EXPECT_CALL(callModeMock,appendIncomingText("Call from: "+to_string(SENDER_PHONE_NUMBER)));
    objectUnderTest.USER_callAchieved(SENDER_PHONE_NUMBER);
}

TEST_F(UserPortTestSuite,shallShowPartnerNotAvailable)
{
    EXPECT_CALL(guiMock,showPeerUserNotAvailable(_));
    objectUnderTest.USER_showPartnerNotAvailable(PHONE_NUMBER);
}

TEST_F(UserPortTestSuite,shallShowMenuAfterCall)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(3);
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    objectUnderTest.USER_showStartMenu();
}

TEST_F(UserPortTestSuite,shallShowEnterPhoneNumber)
{
    EXPECT_CALL(guiMock, setDialMode()).WillOnce(ReturnRef(dialModeMock));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    objectUnderTest.USER_showEnterPhoneNumber();
}

TEST_F(UserPortTestSuite,shallShowDialing)
{
    EXPECT_CALL(guiMock, setAlertMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock,setText(_));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    objectUnderTest.USER_showDialing(SENDER_PHONE_NUMBER);
}

}


