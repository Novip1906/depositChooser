#include "App.h"
#include "Menu.h"
#include "UserDepositManager.h"
#include "server.h"
#include <iostream>

const std::string SERVER_URL = "novip19.pythonanywhere.com";
const std::string TOKEN_FILE = "token.txt";

App::App() {
  this->server = server::Server(SERVER_URL, TOKEN_FILE);
  UserDepositManager::initServer(server); // Передаём сервер, а не параметры
}

void App::start() {
  BankSystem bank(this->server);

  show_main_menu(bank);
}

/*void App::create_deposit(double amount, int duration, bool replenishable) {
    if (!is_logged_in()) return;

    auto response = server.create_deposit(
        amount, duration, replenishable,
        users[current_user_email].getSalary(),
        users[current_user_email].getBroker(),
        users[current_user_email].getSubscription()
    );

    if (response.isSuccess()) {
        UserDepositManager::syncUserDeposits(users[current_user_email]);
    }
} */

std::vector<Deposit> App::load_available_deposits() {
  if (!is_logged_in())
    return {};

  auto response = server.get_deposits(
      1, 36, 0, 1000, 0, users[current_user_email].getSalary(),
      users[current_user_email].getBroker(),
      users[current_user_email].getSubscription());

  return response.isSuccess() ? response.getData() : std::vector<Deposit>();
}

void App::show_deposit_menu() {}
void App::callAssistant() {}
// Геттеры
bool App::is_logged_in() const {

};
