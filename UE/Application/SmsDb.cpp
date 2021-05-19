#include "SmsDb.hpp"
#include <vector>
#include "Sms.hpp"

namespace ue
{
        SmsDb::SmsDb(){}

        Sms SmsDb::getMessage(int index){
           return this->receivedMessages.at(index);
        }

        std::vector<Sms> SmsDb::getAllMessages()
        {
            return this->receivedMessages;
        }

        void SmsDb::addMessage(Sms sms)
        {
            this->receivedMessages.push_back(sms);
        }

}
