#include "Sms.hpp"

namespace ue
{
    Sms::Sms() { }
    Sms::Sms(PhoneNumber senderPhoneNumber, std::string message, bool read, bool sent)
    {
        this->senderPhoneNumberm = senderPhoneNumber;
        this->message = message;
        this->read = read;
        this->sent = sent;
    }
}
