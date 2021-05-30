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
        int size = this->receivedMessages.size();
        if (size > 0){
            return this->receivedMessages;
        } else {
            return NULL;
        }
    }

    void SmsDb::addMessage(Sms sms)
    {
        if(sms != NULL){
            this->receivedMessages.push_back(sms);
        }
    }

    Sms* SmsDb::getLastMessage()
    {
        int index = this->receivedMessages.size() - 1;
        return getMessage(index);
    }
}
