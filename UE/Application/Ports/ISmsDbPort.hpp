#pragma once
#include <vector>
#include "../Models/Sms.hpp"

namespace ue
{
    class ISmsDb
    {
    public:
        virtual ~ISmsDb() = default;
        // Czego wymagam od bazy?
        virtual Sms* getById(int smsId);       // Pobieranie po ID
        virtual std::vector<Sms> getAll();  // Pobranie wszystkich
        virtual void removeById(int smsId);    // Usuwanie po ID
        virtual void removeAll();           // Usuniecie wszystkich
        virtual void insert(Sms sms);       // Dodanie elementu
    };
}


