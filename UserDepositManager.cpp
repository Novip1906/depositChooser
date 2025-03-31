#include "UserDepositManager.h"
#include <iostream>

bool UserDepositManager::syncUserDeposits(const User& user) {
    if (!bankServer) {
        std::cerr << "Сервер не инициализирован!" << std::endl;
        return false;
    }

    auto response = bankServer->get_deposits(
        1, 36, 0, 1000, 0,
        user.getSalary(),
        user.getBroker(),
        user.getSubscription()
    );

    if (response.isSuccess() && response.getCode() == 0) {
        cache[user.getEmail()] = response.getData();
        return true;
    }

    std::cerr << "Не удалось синхронизировать депозиты. Код ошибки: "
              << response.getCode() << std::endl;
    return false;
}

std::vector<Deposit> UserDepositManager::getAvailableDeposits(const User& user) {
    // Если нет в кэше - пробуем синхронизировать
    if (cache.find(user.getEmail()) == cache.end()) {
        syncUserDeposits(user);
    }

    return cache[user.getEmail()];
}

void UserDepositManager::setAvailableDeposits(const User& user,
                                           const std::vector<Deposit>& deposits) {
    cache[user.getEmail()] = deposits;
}

bool UserDepositManager::fullSync(const User& user) {
    return syncUserDeposits(user);
}
