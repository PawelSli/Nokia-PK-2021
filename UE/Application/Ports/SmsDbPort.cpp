#include "SmsDbPort.hpp"
#include <vector>
#include "../Models/Sms.hpp"

namespace ue
{

        SmsDb::SmsDb(){ }
        SmsDb::SmsDb(std::vector<Sms> smsList)
            :messages(smsList) { }

        // TODO: zebranie wszystkich -> getAll()
        std::vector<Sms> SmsDb::getAll()
        {
            return messages;
        }

        void SmsDb::removeLast()
        {
            //TODO
        }

        void SmsDb::removeAll()
        {
            messages.clear();
        }

        void SmsDb::add(Sms sms)
        {
            messages.push_back(sms);
        }

}
