#pragma once
#include "models/Deposit.h"
#include "models/User.h"
#include "server.h"
#include <map>
#include <string>
#include <vector>

class UserDepositManager {
private:
  static inline server::Server *bankServer = nullptr;
  static inline std::map<std::string, std::vector<Deposit>> cache;

public:
  // Инициализация сервера
  static void initServer(server::Server &server) { bankServer = &server; }
  // Синхронизация депозитов с сервером
  static bool syncUserDeposits(const User &user);

  // Получение депозитов пользователя
  static std::vector<Deposit> getAvailableDeposits(const User &user);

  // Установка депозитов (для кэширования)
  static void setAvailableDeposits(const User &user,
                                   const std::vector<Deposit> &deposits);

  // Полная синхронизация
  static bool fullSync(const User &user);
};
