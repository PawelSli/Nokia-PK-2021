#include "Sms.hpp"

namespace ue
{
    // Implementacja konstruktorow
    Sms::Sms() { }
    Sms::Sms(PhoneNumber from, std::string text)
    {
        this->from = from;
        this->text = text;
    }

}