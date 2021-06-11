#pragma once
#include <string.h>
#include "../COMMON/Messages/PhoneNumber.hpp"

namespace ue
{
    using common::PhoneNumber;

    class Sms {
    public:
        PhoneNumber senderPhoneNumber;
        PhoneNumber receiverPhoneNumber;
        std::string message;
        bool read;
        bool sent;
        bool failed;


        Sms();
        Sms(PhoneNumber senderPhoneNumber, PhoneNumber receiverPhoneNumber,  std::string message, bool read, bool sent, bool failed);

        inline bool operator==(const Sms& second) const
        {
            return (senderPhoneNumber==second.senderPhoneNumber
                   && receiverPhoneNumber==second.receiverPhoneNumber
                    && message==second.message);
        }
    };
}

