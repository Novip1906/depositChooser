#pragma once
#include "models/User.h"
#include "models/Deposit.h"
#include "server.h"
#include <vector>
#include <string>
#include <map>

class UserDepositManager {
private:
    static inline server::Server* bankServer = nullptr;
    static inline std::map<std::string, std::vector<Deposit>> cache;

public:
    // Инициализация сервера
    static void initServer(server::Server& server) {
        bankServer = &server;
    }
    // Синхронизация депозитов с сервером
    static bool syncUserDeposits(const User& user);

    // Получение депозитов пользователя
    static std::vector<Deposit> getAvailableDeposits(const User& user);

    // Установка депозитов (для кэширования)
    static void setAvailableDeposits(const User& user, const std::vector<Deposit>& deposits);

    // Полная синхронизация
    static bool fullSync(const User& user);
};
