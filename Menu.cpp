#include "Menu.h"
#include "DepositAssistant.h"
#include "UserDepositManager.h"
#include "server.h"
#include <iostream>
#include <limits>
#include <regex>

BankSystem::BankSystem(server::Server &srv) : server(srv) {
  auto response = server.load_user();

  if (response.isSuccess() && response.getCode() == 0) {
    user = response.getData();
    std::cout << "Вход в систему прошел успешно!\n";
    return;
  }

  std::cout << "Ошибка входа. Код ошибки: " << response.getCode() << "\n";
}

bool BankSystem::register_user(const std::string &email,
                               const std::string &name,
                               const std::string &password,
                               const std::string &repeat_password) {
  if (password != repeat_password) {
    std::cout << "Ошибка: пароли не совпадают!\n";
    return false;
  }

  if (!is_valid_email(email)) {
    std::cout << "Ошибка: Неверный формат электронной почты!\n";
    return false;
  }

  auto response = server.sign_up(email, name, password);
  if (!response.isSuccess()) {
    std::cerr << "Код ошибки: " << response.getCode() << "\n";
    if (response.getCode() == 400) {
      std::cerr << "Недопустимый формат запроса!\n";
    } else if (response.getCode() == 409) {
      std::cerr << "Электронная почта уже существует!\n";
    }
    return false;
  }

  if (response.isSuccess() && response.getCode() == 0) {
    std::cout << "Регистрация прошла успешно!\n";
    return true;
  }

  std::cout << "Ошибка регистрации. Код ошибки: " << response.getCode() << "\n";
  return false;
}

bool BankSystem::login(const std::string &email, const std::string &password) {
  auto response = server.sign_in(email, password);

  if (response.isSuccess() && response.getCode() == 0) {
    current_user_email = email;
    user = response.getData();
    std::cout << "Вход в систему прошел успешно!\n";
    return true;
  }

  std::cout << "Ошибка входа. Код ошибки: " << response.getCode() << "\n";
  return false;
}

void BankSystem::show_profile() {
  if (!is_logged_in()) {
    std::cout << "Ошибка: Не удалось войти в систему!\n";
    return;
  }
  std::cout << "\nПрофиль пользователя:\n"
            << "Имя: " << user.getName() << "\n"
            << "Электронная почта: " << user.getEmail() << "\n"
            << "Зарплатный банк: " << (user.getSalary() ? "Да" : "Нет") << "\n"
            << "Брокерский счет: " << (user.getBroker() ? "Да" : "Нет") << "\n"
            << "Премиум-подписка: " << (user.getSubscription() ? "Да" : "Нет")
            << "\n";
}

void BankSystem::edit_profile(bool salary, bool broker, bool premium) {
  if (!is_logged_in()) {
    std::cout << "Ошибка: вы не зарегистрированы!\n";
    return;
  }

  user.setSalary(salary);
  user.setBroker(broker);
  user.setSubscription(premium);

  auto response = server.save_user(user);
  if (response.isSuccess()) {
    std::cout << "Профиль успешно обновлен!\n";
  } else {
    std::cout << "Не удалось обновить профиль. Код ошибки: "
              << response.getCode() << "\n";
  }
}

void BankSystem::show_user_deposits() {
  if (!is_logged_in()) {
    std::cout << "Ошибка: вы не зарегистрированы!\n";
    return;
  }

  auto deposits = UserDepositManager::getAvailableDeposits(user);

  std::cout << "\nВаши депозиты:\n";
  if (deposits.empty()) {
    std::cout << "Депозиты не обнаружены\n";
    return;
  }

  for (const auto &deposit : deposits) {
    std::cout << "Сумма: " << deposit.getMinSum()
              << " | Срок: " << deposit.getDuration() << "м"
              << "\n";
  }
}

void BankSystem::show_available_deposits() {
  if (!is_logged_in()) {
    std::cout << "Ошибка: вы не зарегистрированы!\n";
    return;
  }

  auto deposits = UserDepositManager::getAvailableDeposits(user);

  std::cout << "\nДоступные депозиты:\n";
  if (deposits.empty()) {
    std::cout << "Нет доступных депозитов\n";
    return;
  }

  for (const auto &deposit : deposits) {
    std::cout << "Сумма: " << deposit.getMinSum()
              << " | Срок: " << deposit.getDuration() << "м"
              << " | Ставка: " << deposit.getMaxPercent() << "%\n";
  }
}

void BankSystem::logout() {
  if (is_logged_in()) {
    server.sign_out();
    current_user_email.clear();
    std::cout << "Успешно вышел из системы\n";
  }
}

bool BankSystem::is_logged_in() const { return user.getEmail() != ""; }

std::string BankSystem::hash_password(const std::string &password) {
  // Simplified hash for demonstration
  std::hash<std::string> hasher;
  return std::to_string(hasher(password));
}

bool BankSystem::is_valid_email(const std::string &email) {
  const std::regex pattern(R"(\w+@\w+\.\w+)");
  return std::regex_match(email, pattern);
}

// Реализация меню
void show_main_menu(BankSystem &bank) {
  int choice;
  std::string email, name, password, repeat_password;

  while (true) {
    if (bank.is_logged_in()) {
      std::cout << "\nГлавное меню:\n"
                << "1. Профиль\n"
                << "2. Вклады\n"
                << "3. Выйти\n"
                << "Введите цифру: ";
      std::cin >> choice;

      switch (choice) {
      case 1:
        show_profile_menu(bank);
        break;
      case 2:
        show_deposit_menu(bank);
        break;
      case 3:
        bank.logout();
        break;
      default:
        std::cout << "Неверный выбор!\n";
      }
    } else {
      std::cout << "\nГлавное меню:\n"
                << "1. Профиль\n"
                << "2. Вклады\n"
                << "3. Выйти\n"
                << "Введите цифру: ";
      std::cin >> choice;

      switch (choice) {
      case 1:
        std::cout << "Электронная почта: ";
        std::cin >> email;
        std::cout << "Пароль: ";
        std::cin >> password;
        bank.login(email, password);
        break;
      case 2:
        std::cout << "Электронная почта: ";
        std::cin >> email;
        std::cout << "Имя: ";
        std::cin >> name;
        std::cout << "Пароль: ";
        std::cin >> password;
        std::cout << "Повторите пароль: ";
        std::cin >> repeat_password;
        bank.register_user(email, name, password, repeat_password);
        break;
      case 3:
        return;
      default:
        std::cout << "Неверный выбор!\n";
      }
    }
  }
}

void show_profile_menu(BankSystem &bank) {
  int choice;
  while (true) {
    bank.show_profile();
    std::cout << "\nМеню профиля:\n"
              << "1. Редактировать профиль\n"
              << "2. Назад\n"
              << "Введите цифру: ";
    std::cin >> choice;

    if (choice == 1) {
      bool salary, broker, premium;
      std::cout << "Зарплата в этом банке (1-Да, 0-Нет): ";
      std::cin >> salary;
      std::cout << "Брокерский счет (1-Да, 0-Нет): ";
      std::cin >> broker;
      std::cout << "Премиум-подписка (1-Да, 0-Нет): ";
      std::cin >> premium;
      bank.edit_profile(salary, broker, premium);
    } else if (choice == 2) {
      break;
    } else {
      std::cout << "Неверный выбор!\n";
    }
  }
}

void show_deposit_menu(BankSystem &bank) {
  int choice;
  while (true) {
    std::cout << "\nМеню вкладов:\n"
              << "1. Показывать доступные вклады\n"
              << "2. Показать мои вклады\n"
              << "3. Создать вклад\n"
              << "4. Помощник по вкладам\n"
              << "5. Назад\n"
              << "Введите цифру: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      bank.show_available_deposits();
      break;
    case 2:
      bank.show_user_deposits();
      break;
    case 3: {
      double amount;
      int duration;
      bool replenishable;

      std::cout << "Сумма: ";
      std::cin >> amount;
      std::cout << "Продолжительность (месяцы): ";
      std::cin >> duration;
      std::cout << "Пополняемый (1-Да, 0-Нет): ";
      std::cin >> replenishable;

      // bank.create_deposit(amount, duration, replenishable);
      break;
    }
    case 4:
      bank.callAssistant();
      break;
    case 5:
      return;
    default:
      std::cout << "Неверный выбор!\n";
    }
  }
}

void BankSystem::callAssistant() {}
