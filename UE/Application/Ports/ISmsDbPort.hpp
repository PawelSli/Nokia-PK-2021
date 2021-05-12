#pragma once
#include <vector>
#include "../Models/Sms.hpp"

namespace ue
{
    class ISmsDb
    {
    public:
        virtual ~ISmsDb() = default;
        virtual std::vector<Sms> getAll();
        virtual void removeLast();
        virtual void removeAll();
        virtual void add(Sms sms);
    };
}


