#pragma once
#include <string.h>
#include "../../COMMON/Messages/PhoneNumber.hpp"

namespace ue
{
    // używam PhoneNumber z COMMON
    using common::PhoneNumber;

    class Sms {
    public:
        unsigned long smsId;    // Id w bazie
        PhoneNumber from;       // numer odbiorcy
        std::string texxt;      // content wiadomosci

        // Konstruktory
        Sms();
        Sms(PhoneNumber from, std::string text);

    };
}

