
/*#include "server.h"
#include "models/Deposit.h"
#include "models/User.h"
#include <map>
#include <string>
#include <vector>

class App {
private:
    server::Server server; // Для общения с сервером
    std::map<std::string, User> users; // Локальное хранилище пользователей
    std::vector<Deposit> deposits; // Локальное хранилище вкладов
    std::string current_user_email; // Текущий пользователь

    // Вспомогательные методы (ранее были в BankSystem)
    bool is_valid_email(const std::string& email);
    std::string hash_password(const std::string& password);
    void save_users_to_file();
    void load_users_from_file();
    void save_deposits_to_file();
    void load_deposits_from_file();

public:
    App(const std::string& serverUrl, const std::string& tokenFilename);
    ~App();

    // Методы для работы с пользователями (аутентификация, профиль)
    server::Server::Response<User> sign_up(const std::string& email, const
std::string& name, const std::string& password); server::Server::Response<User>
sign_in(const std::string& email, const std::string& password);
    server::Server::Response<> sign_out();
    server::Server::Response<User> load_user();
    server::Server::Response<> save_user(const User& user);

    // Методы для работы с вкладами
    server::Server::Response<std::vector<Deposit>> get_deposits(double
duration_min, double duration_max, double percent_min, double percent_max, long
long sum_min, bool reqSalary, bool reqBroker, bool reqPremium); void
create_deposit(double amount, int duration, bool replenishable); void
show_user_deposits(); void show_available_deposits();

    // Методы меню (ранее в Menu.h)
    void show_main_menu();
    void show_profile_menu();
    void show_deposit_menu();
    void callAssistant();
    void Assistant();

    // Геттеры
    bool is_logged_in() const { return !current_user_email.empty(); }
    std::string get_current_user_email() const { return current_user_email; }
}; */

#pragma once

#include "DepositAssistant.h"
#include "Menu.h"
#include "UserDepositManager.h"
#include "json.hpp"
#include "models/Deposit.h"
#include "models/User.h"
#include "server.h"
#include <map>
#include <string>
#include <vector>

using json = nlohmann::json;

class App {
private:
  server::Server server; // Для общения с сервером
  std::map<std::string, User> users; // Локальное хранилище пользователей
  std::string current_user_email; // Текущий пользователь
  BankSystem bankSystem;

  // Вспомогательные методы
  bool is_valid_email(const std::string &email);
  std::string hash_password(const std::string &password);

public:
  App();
  ~App() {};

  void start();

  // Депозиты
  server::Server::Response<std::vector<Deposit>>
  get_deposits(double duration_min = 1, double duration_max = 36,
               double percent_min = 0, double percent_max = 1000,
               long long sum_min = 0, bool reqSalary = false,
               bool reqBroker = false, bool reqPremium = false);
  std::vector<Deposit> load_available_deposits();
  void create_deposit(double amount, int duration, bool replenishable);
  void show_user_deposits();
  void show_available_deposits();

  // Меню
  // void show_main_menu();
  void show_profile_menu();
  void show_deposit_menu();
  void callAssistant();

  // Геттеры
  bool is_logged_in() const;
  std::string get_current_user_email() const;
};
