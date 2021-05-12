#include "SmsDbPort.hpp"
#include <vector>
#include "../Models/Sms.hpp"

namespace ue
{
    class SmsDb
    {
        // TODO: Implementacja konstruktorow
        SmsDb::SmsDb(){ }
        SmsDb::SmsDb(std::vector<Sms> smsList)
            :messages(smsList) { }
        // TODO: zbieranie po smsId -> getById(smsId)
        Sms* SmsDb::getById(int smsId)
        {
            try{
                return &messages.at(id);
            } catch (std::out_of_range& oor){
                return &messages.at(messages.size() - 1);
            }
        }
        // TODO: zebranie wszystkich -> getAll()
        std::vector<Sms> SmsDb::getAll()
        {
            return messages;
        }
        // TODO: usuniecie po smsID -> removeById(smsId)
        void SmsDb::remove(int smsId)
        {
            messages.erase(messages.begin() + id);
            for (int i = id; i < this -> messages.size(); i++)
                messages.at(i).smsId--;
        }
        // TODO: usuniecie wszystkich -> removeALL()
        void SmsDb::removeAll()
        {
            messages.clear();
        }
        // TODO: dodanie elementu -> insert(sms)
        void SmsDb::insert(Sms sms)
        {
            sms.smsId = messages.size();
            messages.puch_back(sms);
        }
    };
}