#pragma once
#include <vector>
#include "ISmsDbPort.hpp"
#include "../Models/Sms.hpp"

namespace ue
{
    class SmsDb : ISmsDb
    {
        std::vector<Sms> messages;

    public:
        // Konstruktory
        SmsDb();
        SmsDb(std::vector<Sms>);
        // Nadpisuje metody z odziedziczonego Interfejsu
        Sms* getById(int smsId) override;
        std::vector<Sms> getAll() override;
        void removeById(int smsId) override;
        void removeAll() override;
        void insert(Sms sms) override;
    };
}

