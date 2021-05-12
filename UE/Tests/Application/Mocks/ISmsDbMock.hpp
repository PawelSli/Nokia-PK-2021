#pragma once
#include <gmock/gmock.h>
#include "Ports/ITimerPort.hpp"
#include "Ports/ISmsDb.hpp"
#include <Models/Sms.hpp>

namespace ue
{
    class ISmsDbMock : public ISmsDb {
    public:
        ISmsDbMock();
        ~ISmsDbMock() override;

        MOCK_METHOD(std::shared_ptr<Sms>, getById, (int), (final));
        MOCK_METHOD(std::vector<Sms>, getAll, (), (final));
        MOCK_METHOD(void, removeById, (int), (final));
        MOCK_METHOD(void, removeAll, (), (final));
        MOCK_METHOD(void, insert, (Sms), (final));
    };
}