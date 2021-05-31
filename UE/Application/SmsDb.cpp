#include "SmsDb.hpp"
#include <vector>
#include "Sms.hpp"

namespace ue
{
    SmsDb::SmsDb(){}

    Sms* SmsDb::getMessage(int index){
        int size = this->receivedMessages.size();
        if(size > 0 && size - 1 <= index){
            return &this->receivedMessages.at(index);
        } else {
            return NULL;
        }
    }

    std::vector<Sms> SmsDb::getAllMessages()
    {
        return this->receivedMessages;
    }

    void SmsDb::addMessage(Sms sms)
    {
        this->receivedMessages.push_back(sms);

    }

    Sms* SmsDb::getLastMessage()
    {
        int index = this->receivedMessages.size() - 1;
        return getMessage(index);
    }
}
