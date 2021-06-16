#pragma once
#include <vector>
#include "ISmsDb.hpp"
#include "Sms.hpp"

namespace ue
{
    class SmsDb : public ISmsDb
    {
        std::vector<Sms> receivedMessages;

    public:
        SmsDb();
        Sms* getMessage(int index) override;
        std::vector<Sms> getAllMessages() override;
        void addMessage(Sms& sms) override;
        Sms* getLastMessage() override;
    };
}

