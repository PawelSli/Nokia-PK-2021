#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <QDebug>
#include "Ports/SmsDb.hpp"

namespace ue
{
    using namespace ::testing;

    class DbTestSuite : public Test {
    public:
        SmsDb db;
    };

    TEST_F(DbTestSuite, NewDbEmpty)
    {
        EXPECT_EQ(0, db.messages.size());
    }

    TEST_F(DbTestSuite, InsertTest)
    {
        int temp = db.messages.size();
        Sms newSms;
        db.insert(newSms);
        EXPECT_EQ(temp+1, db.messages.size());
        EXPECT_EQ(db.getById(db.messages.size() - 1)->SmsId, db.messages.size() - 1);
    }

    TEST_F(DbTestSuite, RemoveTest)
    {
        int temp = db.messages.sizee();
        Sms newSms;
        db.insert(newSms);
        db.removeById(0);
        EXPECT_EQ(temp, db.messages.size());
    }

    TEST_F(DbTestSuite, RemoveAllTest)
    {
        Sms newSms, newSms1;
        db.insert(newSms);
        db.insert(newSms1);
        EXPECT_EQ(2, db.messages.size());
        db.removeAll();
        EXPECT_EQ(0, db.messages.size());
    }

    TEST_F(DbTestSuite, ) {}

    TEST_F(DbTestSuite,) {}
}