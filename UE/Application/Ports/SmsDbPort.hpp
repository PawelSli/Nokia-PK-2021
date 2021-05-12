#pragma once
#include <vector>
#include "ISmsDbPort.hpp"
#include "../Models/Sms.hpp"

namespace ue
{
    class SmsDb : public ISmsDb
    {
        std::vector<Sms> messages;
        bool read;

    public:
        SmsDb();
        SmsDb(std::vector<Sms>);
        std::vector<Sms> getAll() override;
        void removeLast() override;
        void removeAll() override;
        void add(Sms sms) override;
    };
}

