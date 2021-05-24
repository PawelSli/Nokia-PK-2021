#pragma once
#include <vector>
#include "Sms.hpp"

namespace ue
{
    class ISmsDb
    {
    public:
        virtual ~ISmsDb() = default;
        virtual Sms* getMessage(int index) = 0;
        virtual std::vector<Sms> getAllMessages() = 0;
        virtual void addMessage(Sms sms) = 0;
    };
}


