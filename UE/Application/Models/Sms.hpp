#pragma once
#include <string.h>
#include "../../COMMON/Messages/PhoneNumber.hpp"

namespace ue
{
    using common::PhoneNumber;

    class Sms {
    public:
        unsigned long id;
        PhoneNumber senderPhoneNumber;
        std::string message;
        bool read;
        bool sent;

        Sms();
        Sms(PhoneNumber senderPhoneNumber, std::string message, bool read, bool sent);
    };
}

