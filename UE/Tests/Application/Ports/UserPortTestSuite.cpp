#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/UserPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IUeGuiMock.hpp"
#include "SmsDb.hpp"
#include "Sms.hpp"
#include "Mocks/ISmsDbMock.hpp"

namespace ue
{
using namespace ::testing;

class UserPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    SmsDb DATABASE{};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IUserEventsHandlerMock> handlerMock;
    StrictMock<IUeGuiMock> guiMock;
    StrictMock<IListViewModeMock> listViewModeMock;
    StrictMock<ISmsComposeModeMock> smsComposeModeMock;
    StrictMock<ISmsDbMock> smsDbMock;

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
    objectUnderTest.showNotConnected();
}

TEST_F(UserPortTestSuite, shallShowConnecting)
{
    EXPECT_CALL(guiMock, showConnecting());
    objectUnderTest.showConnecting();
}

TEST_F(UserPortTestSuite, shallShowMenuOnConnected)
{
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
    objectUnderTest.showConnected();
}

TEST_F(UserPortTestSuite, shallShowSmsToCreate)
{
    EXPECT_CALL(guiMock, setSmsComposeMode()).WillOnce(ReturnRef(smsComposeModeMock));
    EXPECT_CALL(guiMock, setAcceptCallback(_));
    EXPECT_CALL(guiMock, setRejectCallback(_));
    objectUnderTest.showSmsToCreate();
}

TEST_F(UserPortTestSuite, shallShowSmsReceivedNotification)
{
    EXPECT_CALL(guiMock, showNewSms());
    objectUnderTest.showSmsReceivedNotification();
}

TEST_F(UserPortTestSuite, shallAddMessage)
{
    Sms sms = Sms(PHONE_NUMBER, common::PhoneNumber{12}, "text", false, false, false);
    DATABASE.addMessage(sms);
    int size = DATABASE.getAllMessages().size();
    EXPECT_EQ(1, size);
}

TEST_F(UserPortTestSuite, shallGetMessage)
{
    Sms sms = Sms(PHONE_NUMBER, common::PhoneNumber{12}, "text", false, false, false);
    DATABASE.addMessage(sms);
    Sms *reader = DATABASE.getMessage(0);
    EXPECT_EQ(PHONE_NUMBER, reader->senderPhoneNumber);
    EXPECT_EQ(common::PhoneNumber{12}, reader->receiverPhoneNumber);
    EXPECT_EQ("text", reader->message);
    EXPECT_EQ(false, reader->read);
    EXPECT_EQ(false, reader->sent);
    EXPECT_EQ(false, reader->failed);
}

TEST_F(UserPortTestSuite, shallGetAllMessage)
{
    Sms sms = Sms(PHONE_NUMBER, common::PhoneNumber{12}, "text", false, false, false);
    DATABASE.addMessage(sms);
    DATABASE.addMessage(sms);
    std::vector<Sms> reader = DATABASE.getAllMessages();
    EXPECT_EQ(PHONE_NUMBER, reader[0].senderPhoneNumber);
    EXPECT_EQ(common::PhoneNumber{12}, reader[0].receiverPhoneNumber);
    EXPECT_EQ("text", reader[0].message);
    EXPECT_EQ(false, reader[0].read);
    EXPECT_EQ(false, reader[0].sent);
    EXPECT_EQ(false, reader[0].failed);
    EXPECT_EQ(PHONE_NUMBER, reader[1].senderPhoneNumber);
    EXPECT_EQ(common::PhoneNumber{12}, reader[1].receiverPhoneNumber);
    EXPECT_EQ("text", reader[1].message);
    EXPECT_EQ(false, reader[1].read);
    EXPECT_EQ(false, reader[1].sent);
    EXPECT_EQ(false, reader[1].failed);
}

TEST_F(UserPortTestSuite, shallGetLastMessage)
{
    Sms sms = Sms(PHONE_NUMBER, common::PhoneNumber{12}, "text", false, false, false);
    DATABASE.addMessage(sms);
    Sms *reader = DATABASE.getLastMessage();
    EXPECT_EQ(PHONE_NUMBER, reader->senderPhoneNumber);
    EXPECT_EQ(common::PhoneNumber{12}, reader->receiverPhoneNumber);
    EXPECT_EQ("text", reader->message);
    EXPECT_EQ(false, reader->read);
    EXPECT_EQ(false, reader->sent);
    EXPECT_EQ(false, reader->failed);
}


}
