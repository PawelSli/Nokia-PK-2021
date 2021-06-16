#include "Sms.hpp"

namespace ue
{
    Sms::Sms() { }
    Sms::Sms(PhoneNumber senderPhoneNumber, PhoneNumber receiverPhoneNumber, std::string message, bool read, bool sent, bool failed)
    {
        this->senderPhoneNumber = senderPhoneNumber;
        this->receiverPhoneNumber = receiverPhoneNumber;
        this->message = message;
        this->read = read;
        this->sent = sent;
        this->failed = failed;
    }
}
