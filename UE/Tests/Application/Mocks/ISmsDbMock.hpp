#pragma once

#include <gmock/gmock.h>
#include "ISmsDb.hpp"
#include "Sms.hpp"

namespace ue
{

class Sms;

class ISmsDbMock : public ISmsDb
{

public:
    ISmsDbMock();
    ~ISmsDbMock() override;
    MOCK_METHOD(void, addMessage, (Sms sms), (final));
    MOCK_METHOD(std::vector<Sms>, getAllMessages, (), (final));
    MOCK_METHOD(Sms*, getMessage, (int index), (final));
<<<<<<< HEAD
=======
    MOCK_METHOD(Sms*, getLastMessage, (), (final));
>>>>>>> 389db2ff21770a3cf47ddc6c816eeae2026030fc
};


}
